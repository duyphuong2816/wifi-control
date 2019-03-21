//#include <SoftwareSerial.h>


#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SocketIOClient.h>


SocketIOClient client1;


//const byte Rx = D1;


//const char* ssid = "wemos";
//const char* password = "79797979";
//char host[] = "192.168.43.98";

const char* ssid = "PHUONG";
const char* password = "79797979";
char host[] = "192.168.1.5";

//const char* ssid = "AN CAFE";
//const char* password = "10tohienthanh";
//char host[] = "172.16.0.195";


int port = 3000;
char namespace_esp8266[] = "esp8266";
extern String RID;
extern String Rfull;
String ledData;
int data[]= {0,0,0};
int relay1 = D6;
int relay2 = D7;
int relay3 = D8;
int switch1,switch2,switch3,x;
int button1 = D1;
int button2 = D2;
int button3 = D0;

void setup()
{

  pinMode (relay1,OUTPUT);
  pinMode (relay2,OUTPUT);
  pinMode (relay3,OUTPUT);
  pinMode (button1,INPUT);
  pinMode (button2,INPUT);
  pinMode (button3,INPUT);
  digitalWrite(relay1,1);
  delay(1000);
  digitalWrite(relay2,1);
  delay(1000);
   Serial.begin(9600);
  delay (10);
   Serial.print("Ket noi vao mang ");
   Serial.println(ssid);
   
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(500);
      Serial.print(". ");
    }

    Serial.println();
    Serial.print("Da ket noi WiFi: ");
    Serial.println(WiFi.localIP());
    
    if (!client1.connect(host, port, namespace_esp8266)) {
        Serial.println("Ket noi den server that bai!");
        return;
    }
    Serial.println("Da san sang nhan lenh");
  }
void led()
{
    StaticJsonBuffer<200> jsonBuffer;      
    JsonObject& root = jsonBuffer.parseObject(Rfull);
//    switch1 = root["led"][0];
//    switch2 = root["led"][1];
//    switch3 = root["led"][2];
    digitalWrite(relay1,root["led"][0]);
    digitalWrite(relay2,root["led"][1]);
    digitalWrite(relay3,root["led"][2]);
}

void ping()
{
    client1.send("ping",Rfull);
}

void scanSwitch()
{
  switch1 = digitalRead(button1);
  switch2 = digitalRead(button2);
  switch3 = digitalRead(button3);
  if ((data[0] != switch1)||(data[1] != switch2)||(data[2] != switch3))
  {
    data[0] = switch1;
    data[1] = switch2;
    data[2] = switch3;
    
    digitalWrite(relay1,switch1);
    digitalWrite(relay2,switch2);
    digitalWrite(relay3,switch3);
    
    Serial.println("day la chuoi json duoc goi di");
    ledData = "{\"led\":[" + String(data[0]) + ',' + String(data[1]) + ',' + String(data[2]) + "]}";
    Serial.println(ledData);
    client1.send("LED",ledData);
    x = 0;
  }
}

void loop()
{
  scanSwitch();
    
       if (client1.monitor()) 
   {
        Serial.println(RID);
        Serial.println(Rfull);
        if (RID =="LED") led();
        if (RID == "PING") ping() ;
   }
   
        if (!client1.connected()) {
      client1.connect(host, port, namespace_esp8266);

}}




