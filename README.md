# Medidor de Frequência Cardíaca

### Objetivo:
Permitir que haja um monitoramento remoto do batimento cardíaco de pessoas. Podendo ser um idoso que passa um tempo sozinho ou monitoramento do ritmo cardíaco durante o sono.


Para este projeto você vai precisar:

### Hardware:

* Arduino Uno/Mega/NodeMCU
* ESP01 ou ESP32
* Módulo RTC DS1302
* PulseSensor
* Gravador para ESP

### Software:
* Arduino IDE

### Bibliotecas utilizadas:
* PubSubClient
* ESP8266WiFi
* virtuabotixRTC

## Instruções

Conecte o ESP na gravadora e faça o jumper para habilitar a gravação conforme a documentação do fabricante. (Consulte a documentação do seu fabricante para verificar como fazer isto).

Abra o arquivo *mackenzie_heartmeasurer_ESP_MQTT.ino* e edite-o inserindo os valores corretos para sua rede WiFi e broker MQTT. Após ajustes realize a gravação do firmware no ESP.

Pronto! Qualquer mensagem recebida através da comunicação Serial o seu ESP a enviará ao broker MQTT e poderá ser lido pelo aplicativo conectado ao Broker.

Realize a ligação do ESP e dos demais hardwares no seu arduíno (O esquema de ligação segue na documentação dentro do repositório).

Atente-se aos pinos indicados ou ajuste os pinos utilizados por você no arquivo *mackenzie_heartmeasurer_arduino.ino* 

Ligue o arduíno e coloque o dedo sob o sensor de batimentos e os mesmos já serão enviados ao broker para leitura.

Para leitura dos dados enviados sugerimos o uso do app **IoT MQTT Panel** disponível gratuitamente para Android e iOS, possibilitando a criação de gráficos e outros tipos de visualização.

