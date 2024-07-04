# Sensor DHT11
## Descrição
O sensor DHT11 é responsável pelas leituras de temperatura e umidade do ambiente. O DHT11 opera com faixas de umidade de 20% a 90% com precisão de ±5% e temperatura na faixa de 0°C a 50°C com ±2% de precisão.

![](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/DHT11/DHT11.jpg)

## Datasheet
[Datasheet DHT11](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/DHT11/datasheet-DHT11.pdf)

## Especificações
- Modelo: DHT11
- Tensão de operação: 3 – 5 V (5,5 V máximo)
- Faixa de medição de umidade: 20 a 90% UR
- Faixa de medição de temperatura: 0º a 50ºC
- Faixa de corrente em operação: Máximo de 500mA
- Faixa de corrente em modo espera: 100μA a 150μA
- Precisão de umidade de medição: ± 5,0% UR
- Precisão de medição de temperatura: ± 2,0ºC
- Tempo de resposta: 2 segundos

## Conexão com ESP32
O sensor DHT11 é conectado ao ESP32 conforme a imagem a seguir.
![](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/DHT11/esp32-dht11.png)

## Pinagem
| DHT11 | ESP32 |
| ------ | ------ |
| VCC | Vin |
| DATA | GPIO4 |
| GND | GND |