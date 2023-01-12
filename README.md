# Integração central de Alarme Intelbras com o Home Assistant usando as portas PGM.

Essa integração permite verificar se o alarme está ativo ou com disparo.

Componentes utilizados:

- Central de alarme Intelbras AMT 2018 EG
- Arduino UNO
- Ethernet Shield W5100
- 2 Módulo Relé 1 Canal 5V 10A
- 2 Mini Regulador de Tensão DC Ajustável(Regulado para saida com 5v)

- Arduino IDE
- Home Assistant
- Add-ons Home Assistant: Mosquitto broker

OBS.: Se usar o módulo relé de 12v não precisa do mini regulador de tensão.

1º Passo: Configurar as portas PGM da central de Alarme:
- Video ensinando a configurar
https://www.youtube.com/watch?v=sGBToTigrNQ

2º Passo: Conectar os componentes usando o diagrama como base.

![alt esquema eletrico](https://github.com/renato-dias-lima/integracao-central-alarme-intelbras-ha/blob/main/diagrama-eletrico.jpg)

3º Passo: Gravar o programa na placa Arduino Uno usando o arquivo de exemplo: https://github.com/renato-dias-lima/integracao-central-alarme-intelbras-ha/blob/main/monitoramento-central-alarme.ino

O programa para rodar no arduino foi baseado no video do Lenadro, assista ao video para entender melhor o funcionamento: https://www.youtube.com/watch?v=i3eFdYRcZig
Esse programa pode ser usado no ESP8266 usando a biblioteca para Wifi no lugar da Ethernet.

Obs.: Alterar os parametros conforme a configuração do Home Assistant:

IPAddress ip(192, 168, 1, 198); // IP do Arduino na REDE

//Informações do Servidor MQTT
const char* mqttuser = "";
const char* mqttpass = "";
IPAddress serverMqtt(192, 168, 1, 199); // Ip do Home Assistant para conectar o MQTT

4º Passo: Ligar o Arduino Uno na rede e fonte de alimentação para testar a integração.

![alt projeto](https://github.com/renato-dias-lima/integracao-central-alarme-intelbras-ha/blob/main/projeto-finalizado.jpeg)
* Usei uma caixa que sobrou da instalação do alarme para colocar alguns componentes.
* Usei o arduino com placa de rede porque o sinal do Wifi aonde fica a central de alarme é fraco.

Video do projeto funcionando: https://www.youtube.com/watch?v=0u7Jby-simc

5º Passo: Verificar se aparece a entidade no Home Assitant

![alt projeto](https://github.com/renato-dias-lima/integracao-central-alarme-intelbras-ha/blob/main/entidade-home-assistant.png)

Com a entidade é possível adicionar o card na dashboard para exibir o status do alarme e criar rotinas.
