#include <virtuabotixRTC.h>

//Portas do RTC
#define clk 6
#define dat 7
#define rst 8

int heart = A0; //Define o pino analógico 0 como INPUT do sensor

virtuabotixRTC myRTC(clk, dat, rst); //cria a instância do RTC

int heartMeasurement = 0;

void setup() {
  Serial.begin(115200); //Inicia a comunicação serial na velocidade 115200
  pinMode(heart, INPUT); //Define o pino do sensor como INPUT
}

void loop() {
  heartMeasurement = analogRead(heart); //le o pino do sensor
  myRTC.updateTime(); //atualiza a data/hora 
  char data[80];
  //formata o texto de saída
  snprintf(data, sizeof(data), "{\"data\": \"%d/%d/%d - %2d:%2d:%2d\", \"batimento\": %d}", myRTC.dayofmonth, myRTC.month, myRTC.year, myRTC.hours, myRTC.minutes, myRTC.seconds, heartMeasurement);
  Serial.write(data); //escreve a saída na serial onde o ESP está monitorando para enviar ao MQTT
  delay(3000); //ajusta a frequência de atualização
}
