# Sensor BMP280
## Descrição
O sensor BMP280 é capaz de realizar leituras de pressão atmosférica e temperatura do ambiente através da interface I2C ou SPI e tensão de 3V.

![](https://github.com/eduardozago/weather-station-iot/weather-station-iot/blob/main/sensores/BMP280/BMP280.jpg)

## Datasheet
[Datasheet BMP280](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/DHT11/datasheet-BMP280.pdf)

## Especificações
- Modelo: BMP280
- Tensão de operação: 3 V
- Corrente consumida: 2.7µA
- Interfaces: I2C e SPI
- Faixa de medição de pressão: 300 – 1100hPa (equiv. +9000 à -500m acima/abaixo do nível do mar)
- Faixa de medição de temperatura: -40º à 85ºC
- Precisão de medição de pressão: ± 0,12hPa (equiv. ±1m)
- Precisão de medição de temperatura: ± 1,0ºC

## Conexão com ESP32
O sensor BMP280 é conectado ao ESP32 conforme a imagem a seguir.
![](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/BMP280/esp32-bmp280.png)

## Pinagem
| BMP280 | ESP32 |
| ------ | ------ |
| VCC | 3V3 |
| GND | GND |
| SCL | GPIO22 |
| SCA | GPIO21 |