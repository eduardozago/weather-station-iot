#define CLIENT_ID 1
#define DISABLE_LATER_NTP_UP_RETRY 1
#define CONFIG_MQTT_ADDRESS "[mqtt_host]"
#define CONFIG_MQTT_PORT 1883
#define CONFIG_PREC_TOPIC  "prec"
#define CONFIG_TEMP_TOPIC  "temp"
#define CONFIG_PRES_TOPIC  "pres"
#define CONFIG_HUM_TOPIC  "hum"

#define IT_UP_INT  2000 // em ms, intervalo de tempo entre as medições (seguidas de envios)

#define NTP_UP_INT 7200000 // em ms, intervalo de tempo para atualizar o tempo atual a partir do servidor NTP

#define NTP_UP_RETRY_INT 3000 // em ms, intervalo de tempo entre tentativas de update do tempo atual a partir do servidor NTP

#define RS 2 // Pino do reed switch
#define DHTPIN 4 // Pino do sensor DHT
#define DHTTYPE DHT11 // Tipo do sensor DHT

#define CONFIG_NTP_HOST "[ntp_host]"
#define CONFIG_NTP_TIMEOFFSET 0

#define CONFIG_RTC_TIMEOFFSET -10800
