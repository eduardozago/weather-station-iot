# Estação Meteorológica: Implementação e Monitoramento via IoT
## Introdução

Este projeto consiste na implementação de uma estação meteorológica para monitorar variáveis de temperatura, umidade, pressão atmosférica e precipitação de uma determinada região. O projeto surge com uma alternativa simplificada para monitorar condições climáticas de uma região específica, o que seria inviável com uma estação meteorológica profissional com seu alto custo de implementação e sua operação é complexa. O projeto é constituído de sensores para coletar as informações climáticas e são controlados pelo microcontrolador ESP32 no qual transmite os dados via Wi-Fi através do protocolo MQTT conectando a estação na web.

Esta documentação fornecerá uma descrição detalhada da implementação da estação meteorológica com os componentes de hardware e software bem como os protocolos de comunicação utilizados.

## Descrição do Projeto
Os sensores realizam leituras periódicas dos dados meteorológicos e são conectados ao ESP32, no qual processa os valores lidos e transmite para um Broker MQTT com um tópico que recebe os dados dos dispositivos conectados e encaminha para quem estiver conectado no Broker e inscrito neste tópico. A plataforma IoT Node-RED conecta-se com o Broker MQTT e realiza a inscrição nos tópicos para receber as informações da estação meteorológica. No Node-RED as informações são salvas no PostgreSQL ou banco de dados compatível e as visualizações das variáveis meteorológicas para o usuário são implementadas. 

### Objetivos
- Ler dados dos sensores meteorológicos e transmitir para uma plataforma web de monitoramento.
- Armazenar as informações coletadas em um banco de dados permitindo acesso ao histórico de leituras.
- Visualizar os dados em uma interface web para monitoramento.

## Arquitetura
![](https://github.com/eduardozago/weather-station-iot/blob/main/arquitetura.png)

## Hardware
O hardware é composto por sensores de temperatura, umidade e pressão atmosférica além de um pluviômetro responsável pela medição da precipitação através das gotas de chuva. Todos os componentes de medição são conectados ao microcontrolador. 

O componentes de hardware são:
- ESP32: Microcontrolador 
- [DHT11](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/DHT11): Sensor de temperatura e umidade
- [BMP280](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/BMP280): Sensor de pressão e temperatura
- [Pluviômetro](https://github.com/eduardozago/weather-station-iot/blob/main/sensores/pluviometro): Instrumento de medição da precipitação das chuvas