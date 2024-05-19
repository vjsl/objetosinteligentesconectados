#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi params
const char* ssid = "MACKENZIE_IOT"; //SSID da rede WIFI
const char* passwd = "Mackenzie2024"; //Password da rede WIFI

// MQTT Broker
const char *mqtt_broker = "192.168.0.254"; //IP ou DNS do broker MQTT
const char *topic = "MACKENZIE/heartmeasurer"; //Tópico MQTT
const char *mqtt_user = "vitor"; //Usuario do servidor MQTT
const char *mqtt_passwd = "Vitor@2024"; //Senha do servidor MQTT
const int mqtt_port = 1883; //Porta do MQTT

bool mqtt_status = 0;

WiFiClient espClient; //Instância da client WiFi
PubSubClient client(espClient); //Instância da lib responsável pelo envio das mensagens ao broker MQTT

bool connectMQTT();

bool connectMQTT() {
  byte tentativa = 0;
  client.setServer(mqtt_broker, mqtt_port);

  do {
    String client_id = "HEARTMACK-";
    client_id += String(WiFi.macAddress());

    if(client.connect(client_id.c_str(), mqtt_user, mqtt_passwd)) {
      Serial.println("Conectado ao servidor MQTT");
    } else {
      Serial.print("Falha na conexão :(");
      Serial.print(client.state());
      Serial.println();
      Serial.printf("Tentativa: %d", tentativa);
      delay(2000);
    }
    tentativa++;
  } while (!client.connected() && tentativa < 10);

  if (tentativa < 10) {
    client.publish(topic, "Teste de conexão <3");
    return 1;
  } else {
    Serial.println("Não conectado :(");
    return 0;
  }
}


void setup() {
  Serial.begin(115200); //Inicializa o serial na velocidade 115200
  WiFi.begin(ssid, passwd); //Inicializa o Wifi com o SSID e SENHA

  Serial.print("Conectando...");
  while(WiFi.status() != WL_CONNECTED) { //Enquanto aguarda a conexão imprime um . a cada 500ms
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado ao Wifi!");

  Serial.println(WiFi.localIP()); //Printa no Serial o IP obtido do roteador

  mqtt_status = connectMQTT(); //Inicia a conexão com o servidor MQTT

}

void loop() {
  if(mqtt_status) {
    client.loop();
    if (Serial.available() > 0) {
      String message = Serial.readString(); //Le o payload da comunicação serial
      message.trim();
      Serial.println(message.c_str()); //Printa no console a mensagem recebida
      client.publish(topic, message.c_str()); //Publica a mensagem no tópico definido
      Serial.println("Mensagem enviada");
    }
    
  }
}
