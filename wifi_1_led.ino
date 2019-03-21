#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include "string.h"
const char *ssid = "wemos";      // tên của AP
const char *password = "79797979"; // mật khẩu truy cập, để rỗng nếu không muốn cài mật khẩu

boolean relayPin[]={14,12,13};
boolean switchPin[]={16,5,4};
boolean value[3],latch,flag[3];
char* text[3];
String msg;
int i;
 
ESP8266WebServer server(80);            // khai báo server
/* 
void handleRoot() {                     // tạo giao diện Web server
    response();
}
*/
 void handle1On() {                                  //relay 1
  digitalWrite(relayPin[0], 0);                        // active 0
  server.send(200,"test/plain","1 On");
  Serial.printf("active..1\n");
}
 void handle1Off() {
  digitalWrite(relayPin[0], 1);
  server.send(200,"test/plain","1 Off");
  Serial.printf("active..11\n");
}

 void handle2On() {                                  //relay 2
  digitalWrite(relayPin[1], 0);
  server.send(200,"test/plain","2 On");
  Serial.printf("active..2\n");
}
 void handle2Off() {
  digitalWrite(relayPin[1], 1);
  server.send(200,"test/plain","2 Off");
  Serial.printf("active..21\n");
}

 void handle3On() {                                  //relay 3
  digitalWrite(relayPin[2], 0);
  server.send(200,"test/plain","3 On");
  Serial.printf("active..3\n");
}
 void handle3Off() {
  digitalWrite(relayPin[2], 1);
  server.send(200,"test/plain","3 Off");
  Serial.printf("active.31\n");
}


 void FastOn() {                                  //full option
  msg="";
  for (i=0;i<3;i++){
  digitalWrite(relayPin[i], 0);
  msg+=String(i+1)+" On; ";
  Serial.println(msg);
 }
 server.send(200,"test/plain",msg);
 msg="";
 }
 
 void FastOff() {
  msg="";
  for (i=0;i<3;i++){
  digitalWrite(relayPin[i], 1);
  msg+=String(i+1)+ " Off; " ;
  Serial.println(msg);
 }
 server.send(200,"test/plain",msg);
 msg="";
 }


void Check(){                                             //check status
  msg="";
  for (i=0;i<3;i++){
   if(digitalRead(relayPin[i])==0)
     text[i]= " On; ";
   else 
     text[i] = " Off; ";
   msg+=String(i+1)+String(text[i]) ;
  }
  server.send(200,"test/plain",msg);
  msg="";
  }


void Switch(){

  for (i=0;i<3;i++){
    if (value[i]!=digitalRead(switchPin[i])){
      value[i] = digitalRead(switchPin[i]);    
      digitalWrite(relayPin[i],!value[i]);

  }}}
void setup() {
    delay(1000);
    for (i=0;i<3;i++){
    pinMode(relayPin[i],OUTPUT);
    digitalWrite(relayPin[i],1);
    pinMode(switchPin[i],INPUT);
    }
    
   
    Serial.begin(9600);
    WiFi.begin(ssid, password); 
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
     Serial.println("HTTP server beginned");

     server.begin();  
    //server.on("/", handleRoot);   
    server.on("/relay1On", handle1On);                //relay 1
    server.on("/relay1Off", handle1Off);               
    
    server.on("/relay2On", handle2On);              //relay 2
    server.on("/relay2Off", handle2Off);
    
    server.on("/relay3On", handle3On);              //relay 3
    server.on("/relay3Off", handle3Off);

    server.on("/FastOn", FastOn);              //control 3 relay
    server.on("/FastOff", FastOff);
  
    server.on("/Check",Check);              // check status  
}


void loop1(){
  server.handleClient();
}
void loop2(){
  Switch();
}

void loop() {
    loop1();
    loop2();
}
