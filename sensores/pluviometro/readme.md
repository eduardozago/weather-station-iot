# Pluviômetro
O pluviômetro atua no monitoramento da quantidade de precipitação de chuvas de uma determinada região. O pluviômetro possui em seu interior uma báscula para a medição da precipitação da chuva onde a cada 0,25mm o sensor interno emite um pulso, que pode ser lido e interpretado por um microcontrolador.

![](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/pluviometro/pluviometro.png)

## Especificações
- Modelo: PB10
- Tensão de operação: 3 a 30 VDC
- Tipo: Digital
- Leitura: a cada 0,25mm
- Diâmentro do coletor: ~147mm
- Erro máximo: 4% (até 30 mm/h), 5% (até 50mm/h), 7% (até 90 mm/h)

## Conexão com ESP32
A imagem a seguir mostro como o pluviômetro é conectado ao ESP32.

![](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/pluviometro/esp32-pluviometro.png)

## Pinagem
| Pluviômetro | ESP32 |
| ------ | ------ |
| VCC | Vin/5V |
| DATA | GPIO2 |