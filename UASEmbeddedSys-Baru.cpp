#include <Arduino.h>
// Memasukkan Library ESP8266
#include <ESP8266WiFi.h>

// Inisiasi pin sensor dan pin relay ke pompa
const int sensorPin = A0;
int pump = 12; //GPIO 12 = Pin D6

// ApiKey untuk mengkoneksikan modul ESP8266 ke website ThinkSpeak
String apiKey = "I5KKBNZQVYRN2W0D";

// Untuk mengkoneksikan modul ESP8266 pada jaringan WiFi
const char *ssid = "Galaxy A117237";
const char *pass = "ndtz3764";
const char *server = "api.thingspeak.com";

WiFiClient client;

unsigned long myChannelNumber = 1989517; //channel ID
const char * myWriteAPIKey = "I5KKBNZQVYRN2W0D"; //write APIKey

void setup() { 
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(pump, OUTPUT);

  // Inisiasi awal untuk koneksi ke jaringan WiFi
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid,pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  }

void loop() {
  // Pembacaan sensor Hygrometer
  int sensorValue = (analogRead(A0)/1024)*100;
  Serial.print("Nilai Kelembapan : ");
  Serial.print(sensorValue);
  Serial.println("%");

  // Koneksi dan pengiriman data ke ThinkSpeak
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com  
  {
   String postStr = apiKey;
   postStr +="&field1=";
   postStr += String(sensorValue);
   postStr += "\r\n\r\n";
   
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(postStr.length());
   client.print("\n\n");
   client.print(postStr);

   Serial.println(". Send to Thingspeak.");
   
   // Kondisi pembacaan sensor untuk menyalakan pompa air
   if (sensorValue > 70) {
    digitalWrite(pump, HIGH);
  }
  else {
    digitalWrite(pump, LOW);
  }
  }
  client.stop();
  
  Serial.println("Waiting...");
  delay(1000);
}