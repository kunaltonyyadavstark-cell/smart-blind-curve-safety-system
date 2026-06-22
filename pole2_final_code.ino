#include <WiFi.h>
#include <esp_now.h>

#define RCWL 13
#define TRIG 26
#define ECHO 14
#define BUZZER 27
#define LED 25

uint8_t pole1Mac[] = {0x84,0x1F,0xE8,0x68,0x4A,0xD4};

bool warning=false;

typedef struct{
char msg[10];
}message;

message data;

void sendMessage(String text){

 strcpy(data.msg,text.c_str());

 esp_now_send(pole1Mac,(uint8_t*)&data,sizeof(data));

}

void receive(const esp_now_recv_info_t *info,const uint8_t *incoming,int len){

 memcpy(&data,incoming,sizeof(data));

 if(String(data.msg)=="ALERT"){

   warning=true;

 }

 if(String(data.msg)=="CLEAR"){

   warning=false;

 }

}

void setup(){

 Serial.begin(115200);

 pinMode(RCWL,INPUT);

 pinMode(TRIG,OUTPUT);

 pinMode(ECHO,INPUT);

 pinMode(BUZZER,OUTPUT);

 pinMode(LED,OUTPUT);

 WiFi.mode(WIFI_STA);

 esp_now_init();

 esp_now_register_recv_cb(receive);

 esp_now_peer_info_t peer={};

 memcpy(peer.peer_addr,pole1Mac,6);

 esp_now_add_peer(&peer);

}

void loop(){

 if(digitalRead(RCWL)==HIGH){

   sendMessage("ALERT");

   delay(3000);

 }

 if(warning){

   digitalWrite(LED,HIGH);

   digitalWrite(BUZZER,HIGH);

 }else{

   digitalWrite(LED,LOW);

   digitalWrite(BUZZER,LOW);

 }

 long duration,distance;

 digitalWrite(TRIG,LOW);

 delayMicroseconds(2);

 digitalWrite(TRIG,HIGH);

 delayMicroseconds(10);

 digitalWrite(TRIG,LOW);

 duration=pulseIn(ECHO,HIGH);

 distance=duration*0.034/2;

 if(distance<15 && distance>0){

   sendMessage("CLEAR");

 }

 delay(100);

}