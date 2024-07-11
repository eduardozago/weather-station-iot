# Estação Meteorológica: Implementação e Monitoramento via IoT
## Introdução

Este projeto consiste na implementação de uma estação meteorológica para monitorar variáveis de temperatura, umidade, pressão atmosférica e precipitação de uma determinada região. O projeto surge com uma alternativa simplificada para monitorar condições climáticas de uma região específica, o que seria inviável com uma estação meteorológica profissional com seu alto custo de implementação e sua operação complexa. O projeto é constituído de sensores para coletar as informações climáticas e são controlados pelo microcontrolador ESP32 no qual transmite os dados via Wi-Fi através do protocolo MQTT conectando a estação na web.

Esta documentação fornecerá uma descrição detalhada da implementação da estação meteorológica com os componentes de hardware e software bem como os protocolos de comunicação utilizados.

## Descrição do Projeto
Os sensores realizam leituras periódicas dos dados meteorológicos e são conectados ao ESP32, no qual processa os valores lidos e transmite para um Broker MQTT com um tópico que recebe os dados dos dispositivos conectados e encaminha para quem estiver conectado no Broker e inscrito nesse tópico. A plataforma IoT Node-RED conecta-se com o Broker MQTT e realiza a inscrição nos tópicos para receber as informações da estação meteorológica. No Node-RED as informações são salvas no PostgreSQL ou banco de dados compatível e são implementadas as visualizações das variáveis meteorológicas para o usuário. Além disso, o ESP32 realiza uma conexão com um servidor NTP para sincronização de relógio, garantindo a confiabilidade do registro do momento em que as leituras ocorrem. 

### Objetivos
- Ler e transmitir para uma plataforma web de monitoramento leituras dos sensores meteorológicos de temperatura, pressão, umidade e precipitação.
- Receber os dados na plataforma IoT Node-RED e gerar visualizações para monitoramento.
- Armazenar os valores lidos em um banco de dados (PostgreSQL ou compatível) permitindo acesso ao histórico de leituras.

## Arquitetura
![](https://github.com/eduardozago/weather-station-iot/blob/main/arquitetura.png)

## Hardware
O hardware é composto por sensores de temperatura, umidade e pressão atmosférica além de um pluviômetro responsável pela medição da precipitação através das gotas de chuva. Todos os componentes de medição são conectados ao microcontrolador. 

O componentes de hardware são:
- ESP32 (ESP-WROOM-32D): Microcontrolador 
- [DHT11](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/DHT11): Sensor de temperatura e umidade
- [BMP280](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/BMP280): Sensor de pressão e temperatura
- [Pluviômetro](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/pluviometro): Instrumento de medição da precipitação das chuvas

A figura a seguir mostra como são conectados os componentes.

![](https://github.com/eduardozago/weather-station-iot/blob/main/hardware.png)

## Pinagem
| BMP280    | DHT11     | Pluviômetro | ESP32 |
| ------    | ------    | ------    | ------ |
| VCC       | VCC       | -         | 3V3 |
| -       | -         | VCC         | Vin/5V |
| GND       | GND       | -         | GND |
| -       | -         | DATA         | GPIO2 |
| -       | DATA      | -         | GPIO4 |
| SDA       | -         | -         | GPIO21 |
| SCL       | -         | -         | GPIO22 |

## Software 

A integração com o do software com o hardware ocorre através da plataforma Node-RED, no qual faz a conexão com o Broker MQTT e recebe os dados remotamente da estação meteorológica. O Node-RED é responsável por armazenar no banco de dados os valores lidos e por gerar visualizações para o monitoramento das variáveis meteorológicas.

O banco de dados utilizado é o PostgreSQL ou banco de dados compatível. Além disso, o ESP32 conecta-se à um servidor NTP para sincronizar seu relógio e garantir a precisão do registro do momento em que a leitura é feita.

## Conclusão
