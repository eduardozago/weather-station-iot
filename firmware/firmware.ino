#include "DHT.h"

#include "DHT.h"

#include <WiFi.h>
#include <PubSubClient.h>

#include <Wire.h>
#include <Adafruit_BMP280.h>

#include <NTPClient.h>
#include <WiFiUdp.h>

#include <ESP32Time.h>

#include <ArduinoJson.h>

// credenciais de acesso à rede WIFI e ao servidor MQTT
#include "credentials.ino"

#define CLIENT_ID 1

#define RS 2 // Pino do reed switch
#define DHTPIN 4 // Pino do sensor DHT11
#define DHTTYPE DHT11 // Tipo do sensor DHT11

#define UP_IT_INT  2000 // en ms, intervalo de tempo entre as medições (seguidas de envios)

#define UP_NTP_INT 7200000 // em ms, intervalo de tempo para atualizar o tempo atual a partir do servidor NTP

char wifi_ssid[] = CRED_WIFI_SSID;
char wifi_pass[] = CRED_WIFI_PASS;

char mqtt_user[] = CRED_MQTT_USER;
char mqtt_pass[] = CRED_MQTT_PASS;

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

const char broker[] = "[mqtt_host]";
int        port     = 1883;
const char prec_topic[]  = "prec";
const char temp_topic[]  = "temp";
const char pres_topic[]  = "pres";
const char hum_topic[]  = "hum";

//Variáveis relativas ao BMP280

Adafruit_BMP280 bmp;

//Variáveis relativas ao DHT11

int value = 0;

DHT dht(DHTPIN, DHTTYPE);

// Variáveis relativas ao pluviômetro
int val = 0;
int old_val = 0;
volatile unsigned long RSCOUNT = 0;
float precipitation_depth = 0.0;

unsigned int debounce_time = 50;
unsigned long last_rs_time = 0;

// ntp
WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "[ntp_host]", 0, UP_NTP_INT); // NTP está definido para UTC (0)

// rtc
ESP32Time rtc(-10800); // RTC está definido para UTC-3 (-10800)

void cb(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem obtida: <");
  Serial.print(topic);
  Serial.print("> ");
  for (int i = 0; i < length; i++) {
   Serial.print((char)payload[i]);
  }
  Serial.println();
}

void print_cur_state_msg(int cur_state) {
  switch(cur_state) {
      case MQTT_CONNECTION_TIMEOUT:
        Serial.println("O servidor não respondeu dentro do tempo de espera");
        break;
      case MQTT_CONNECTION_LOST:
        Serial.println("A conexão de rede foi interrompida");
        break;
      case MQTT_CONNECT_FAILED:
        Serial.println("Falha na conexão de rede");
        break;
      case MQTT_DISCONNECTED:
        Serial.println("Cliente não conectado");
        break;
      case MQTT_CONNECTED:
        Serial.println("Cliente conectado");
        break;
      case MQTT_CONNECT_BAD_PROTOCOL:
        Serial.println("O servidor não suporta a versão solicitada do MQTT");
        break;
      case MQTT_CONNECT_BAD_CLIENT_ID:
        Serial.println("O servidor rejeitou o identificador do cliente");
        break;
      case MQTT_CONNECT_UNAVAILABLE:
        Serial.println("O servidor não conseguiu aceitar a conexão");
        break;
      case MQTT_CONNECT_BAD_CREDENTIALS:
        Serial.println("O nome de usuário ou senha foram rejeitados");
        break;
      case MQTT_CONNECT_UNAUTHORIZED:
        Serial.println("O cliente não foi autorizado para se conectar");
        break;
      default:
        break;
     }
}

void reconnect_mqtt() {
  int cur_state;
  while (!mqtt_client.connected()) {
    Serial.println("Tentando conectar-se ao MQTT");
    String client_id = "ESP32#" + String(CLIENT_ID, 16);

    if (mqtt_client.connect(client_id.c_str(), mqtt_user, mqtt_pass)) {
     Serial.println("Conectado");
    } else {
     Serial.println("Falhou ao conectar-se ao MQTT");

     cur_state = mqtt_client.state();

     Serial.print(F("Estado atual do cliente: "));
     Serial.println(cur_state);
     print_cur_state_msg(cur_state);

     Serial.println("Tentando novamente em 3 segundos");

     delay(3000);
    }
  }
}

void IRAM_ATTR precipitation_isr () {
  if ((millis() - last_rs_time) > debounce_time ) {
    RSCOUNT = RSCOUNT + 1;
    last_rs_time = millis();
    Serial.println("Contagem de pulsos do REED switch incrementada");
  }
}

void get_precipitation(){
    precipitation_depth = RSCOUNT * 0.25; /* altura da precipitação em mm */

    Serial.print("Contagem de pulsos do REED Switch: ");
    Serial.println(RSCOUNT);

    Serial.print("Precipitação: ");
    Serial.print (precipitation_depth);
    Serial.println(" mm");
}

void setup() {
  Serial.begin(9600); /* velocidade monitor serial */

  delay(50);

  // Configuração do WIFI
  Serial.println();
  Serial.print(F("Conectando à rede "));
  Serial.println(wifi_ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(F("Conectado ao WiFi"));
  Serial.print(F("Endereço IP: "));
  Serial.println(WiFi.localIP());

  // Configuração do MQTT
  mqtt_client.setServer(broker, 1883);
  mqtt_client.setCallback(cb);

  // Configuração do RS
  pinMode(RS, INPUT_PULLUP);
  attachInterrupt(RS, precipitation_isr, FALLING);

  // Configuração do BMP280
  unsigned int bmp_status;

  bmp_status = bmp.begin(0x76);
  if (!bmp_status) {
    uint8_t sensor_id = bmp.sensorID();
    Serial.print("ID do Sensor: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.println(F("Não foi possível encontrar um sensor BMP280 válido, verifique as conexões ou tente um endereço diferente!"));

    delay(500);
    
    while (1) delay(10);
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo de operação */
                  Adafruit_BMP280::SAMPLING_X2,     /* Oversampling da temperatura */
                  Adafruit_BMP280::SAMPLING_X16,    /* Oversampling da pressão */
                  Adafruit_BMP280::FILTER_X16,      /* Nível de filtragem para dados do sensor. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Tempo de espera. */
  
  timeClient.begin();

  delay(10);

  timeClient.update();

  delay(10);

  rtc.setTime( timeClient.getEpochTime() );
}

void loop() {

  unsigned long last_it_time = 0;

  JsonDocument doc;

  String mqtt_payload;

  while(1) {

    if (millis() - last_it_time > 2000 ) {
      if (!mqtt_client.connected()) {
        reconnect_mqtt();
      }

      mqtt_client.loop();

      Serial.println( millis() - last_it_time );
      last_it_time = millis();

      get_precipitation();

      doc["ts"] = rtc.getLocalEpoch();
      doc["val"] = precipitation_depth;

      serializeJson(doc, mqtt_payload);

      mqtt_client.publish(prec_topic, mqtt_payload.c_str());

      delay(50);

      float temp = bmp.readTemperature();

      Serial.print(F("Temperatura = "));
      Serial.print(temp);
      Serial.println(" °C");

      doc["ts"] = rtc.getLocalEpoch();
      doc["val"] = temp;

      serializeJson(doc, mqtt_payload);

      mqtt_client.publish(temp_topic, mqtt_payload.c_str());

      delay(50);

      float pres = bmp.readPressure();

      Serial.print(F("Pressão = "));
      Serial.print(pres);
      Serial.println(" Pa");

      doc["ts"] = rtc.getLocalEpoch();
      doc["val"] = pres;

      serializeJson(doc, mqtt_payload);

      mqtt_client.publish(pres_topic, mqtt_payload.c_str());

      delay(50);

      float hum = dht.readHumidity();

      Serial.print(F("Umidade: "));
      Serial.println(hum);

      doc["ts"] = rtc.getLocalEpoch();
      doc["val"] = hum;

      serializeJson(doc, mqtt_payload);

      mqtt_client.publish(hum_topic, mqtt_payload.c_str());

      delay(50);

      Serial.println( rtc.getEpoch() );
      Serial.println( rtc.getTime("%A, %B %d %Y %H:%M:%S") );

      if(timeClient.update()) {
        delay(10);
        rtc.setTime( timeClient.getEpochTime() );
      }
      
    }
  }

}
