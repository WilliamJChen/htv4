#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>
#define WIFI_SSID "W"
#define WIFI_PASSWORD "password"
#define FIREBASE_HOST "sensor-4876a.firebaseio.com"
#define FIREBASE_AUTH "QutsPH9xmmp9sGLsNp4IzpZ3J51qZOE1EE1JY3s2"

int sensor = 13;
bool motion = false;

void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Connected!");
  }else{
    wifiConnect();
  }
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Connected!");
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop() {
  // put your main code here, to run repeatedly:
  long state = digitalRead(sensor);
  if(state == HIGH && motion==false){
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["long"] = -15;
    root["lat"] = -45;
    root["animal"] = "elephant";
    Firebase.push("/Points/", root);
    Serial.println("fire");
    if(Firebase.failed()){
      Serial.println("rip");  
      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    }else{
      Serial.println("yes");  
    }
    motion = true;
    delay(2000);
  }else{
    Serial.println("no motion");  
    motion = false;
    delay(1000);
  }
}
void wifiConnect()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID); Serial.println(" ...");
  int teller = 0;
  while (WiFi.status() != WL_CONNECTED)
  {                                       // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++teller); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}
