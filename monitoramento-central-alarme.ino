#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 198);

//Informações do Servidor MQTT
const char* mqttuser = "";
const char* mqttpass = "";
IPAddress serverMqtt(192, 168, 1, 199);

void callback(char* topic, byte* payload, unsigned int length) {
  
}

EthernetClient ethClient;
PubSubClient ConexaoMQTT(serverMqtt, 1883, callback, ethClient);

const int PINdisparoCentralAlarme = 12;
const int PINativacaoCentralAlarme = 13;

int UltimoValorPINdisparoCentralAlarme = 0;
int TimeCounterPINdisparoCentralAlarme = 0;

int UltimoValorPINativacaoCentralAlarme = 0;
int TimeCounterPINativacaoCentralAlarme = 0;

void reconnect() {
  while (!ConexaoMQTT.connected()) {
    Serial.println("Conectando ao Broker MQTT");
    ConexaoMQTT.connect("arduinoUno",mqttuser,mqttpass);
    delay(3000);
  }
  Serial.println("MQTT conectado");
}

void setup(){
  Serial.begin(115200);
  
  Ethernet.begin(mac, ip);

  delay(5000);

  if (!ConexaoMQTT.connected()) {
    reconnect();
  }
  
  pinMode(PINdisparoCentralAlarme, INPUT);
  pinMode(PINativacaoCentralAlarme, INPUT);

  //Configura Sensores através do MQTT Discovery do Home Assistant
  String sensorDisparoCentralAlarme = "{\"expire_after\": \"600\", \"icon\": \"mdi:gesture-tap-button\", \"name\": \"Central Alarme Disparo\", \"state_topic\": \"centralAlarme/interruptor1/state\"}";
  ConexaoMQTT.publish("homeassistant/binary_sensor/centralAlarme/interruptor1/config",sensorDisparoCentralAlarme.c_str(),false);

  String sensorAtivacaoCentralAlarme = "{\"expire_after\": \"600\", \"icon\": \"mdi:gesture-tap-button\", \"name\": \"Central Alarme Ativacao\", \"state_topic\": \"centralAlarme/interruptor2/state\"}";
  ConexaoMQTT.publish("homeassistant/binary_sensor/centralAlarme/interruptor2/config",sensorAtivacaoCentralAlarme.c_str(),false);

  //Primeira leitura
  int LeituraPINdisparoCentralAlarme = digitalRead(PINdisparoCentralAlarme);
  Serial.print("Primeira Leitura: ");
  Serial.println(LeituraPINdisparoCentralAlarme);
  if (LeituraPINdisparoCentralAlarme == 0) {
    UltimoValorPINdisparoCentralAlarme = LeituraPINdisparoCentralAlarme;
    ConexaoMQTT.publish("centralAlarme/interruptor1/state","OFF");
  } else if (LeituraPINdisparoCentralAlarme == 1) {
    UltimoValorPINdisparoCentralAlarme = LeituraPINdisparoCentralAlarme;
    ConexaoMQTT.publish("centralAlarme/interruptor1/state","ON");
  }

  int LeituraPINativacaoCentralAlarme = digitalRead(PINativacaoCentralAlarme);
  Serial.print("Primeira Leitura: ");
  Serial.println(LeituraPINativacaoCentralAlarme);
  if (LeituraPINativacaoCentralAlarme == 0) {
    UltimoValorPINdisparoCentralAlarme = LeituraPINativacaoCentralAlarme;
    ConexaoMQTT.publish("centralAlarme/interruptor2/state","OFF");
  } else if (LeituraPINativacaoCentralAlarme == 1) {
    UltimoValorPINdisparoCentralAlarme = LeituraPINativacaoCentralAlarme;
    ConexaoMQTT.publish("centralAlarme/interruptor2/state","ON");
  }

}

void loop() {

  if (!ConexaoMQTT.connected()) {
    reconnect();
  }
  
  int LeituraPINdisparoCentralAlarme = digitalRead(PINdisparoCentralAlarme);
  int LeituraPINativacaoCentralAlarme = digitalRead(PINativacaoCentralAlarme);
  Serial.println(LeituraPINdisparoCentralAlarme);
  Serial.println(LeituraPINativacaoCentralAlarme);

  if (LeituraPINdisparoCentralAlarme != UltimoValorPINdisparoCentralAlarme) {
    if (LeituraPINdisparoCentralAlarme == 0) {
      UltimoValorPINdisparoCentralAlarme = LeituraPINdisparoCentralAlarme;
      ConexaoMQTT.publish("centralAlarme/interruptor1/state","OFF");
    } else if (LeituraPINdisparoCentralAlarme == 1) {
      UltimoValorPINdisparoCentralAlarme = LeituraPINdisparoCentralAlarme;
      ConexaoMQTT.publish("centralAlarme/interruptor1/state","ON");
    }
  }

  if (TimeCounterPINdisparoCentralAlarme < 600) {
    TimeCounterPINdisparoCentralAlarme++;
  } else if (TimeCounterPINdisparoCentralAlarme >= 600) {
    if (LeituraPINdisparoCentralAlarme == 0) {
      UltimoValorPINdisparoCentralAlarme = LeituraPINdisparoCentralAlarme;
      ConexaoMQTT.publish("centralAlarme/interruptor1/state","OFF");
    } else if (LeituraPINdisparoCentralAlarme == 1) {
      UltimoValorPINdisparoCentralAlarme = LeituraPINdisparoCentralAlarme;
      ConexaoMQTT.publish("centralAlarme/interruptor1/state","ON");
    }
    TimeCounterPINdisparoCentralAlarme = 0;
  }

  if (LeituraPINativacaoCentralAlarme != UltimoValorPINativacaoCentralAlarme) {
    if (LeituraPINativacaoCentralAlarme == 0) {
      UltimoValorPINativacaoCentralAlarme = LeituraPINativacaoCentralAlarme;
      ConexaoMQTT.publish("centralAlarme/interruptor2/state","OFF");
    } else if (LeituraPINativacaoCentralAlarme == 1) {
      UltimoValorPINativacaoCentralAlarme = LeituraPINativacaoCentralAlarme;
      ConexaoMQTT.publish("centralAlarme/interruptor2/state","ON");
    }
  }

  if (TimeCounterPINativacaoCentralAlarme < 600) {
    TimeCounterPINativacaoCentralAlarme++;
  } else if (TimeCounterPINativacaoCentralAlarme >= 600) {
    if (LeituraPINativacaoCentralAlarme == 0) {
      UltimoValorPINativacaoCentralAlarme = LeituraPINativacaoCentralAlarme;
      ConexaoMQTT.publish("centralAlarme/interruptor2/state","OFF");
    } else if (LeituraPINativacaoCentralAlarme == 1) {
      UltimoValorPINativacaoCentralAlarme = LeituraPINativacaoCentralAlarme;
      ConexaoMQTT.publish("centralAlarme/interruptor2/state","ON");
    }
    TimeCounterPINativacaoCentralAlarme = 0;
  }

 delay(500);
}
