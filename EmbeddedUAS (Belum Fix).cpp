#include <Arduino.h>

#include <LiquidCrystal_I2C.h>

//ARDUINO BASED SOIL MOISTURE DETECTOR

const int pinDigital = A0; //inisialisasi pin sensor
const int relay = 6;       //inisialisasi pin relay 
const int ledGreen = 7;    //inisialisasi pin led hijau
const int ledYellow = 8;   //inisialisasi pin led kuning
const int ledRed = 9;      //inisialisasi pin merah
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
lcd.init();
Serial.begin (9600);          //memanggil serial monitor
lcd.begin(16,2);
lcd.backlight();
lcd.print("Projek DASMIK");
lcd.clear();
pinMode(pinDigital, INPUT);   //menetapkan pin A0 sebagai input
pinMode(relay, OUTPUT);       //menetapkan pin 6 sebagai output
pinMode(ledGreen, OUTPUT);    //menetapkan pin 7 sebagai output
pinMode(ledYellow, OUTPUT);   //menetapkan pin 8 sebagai output
pinMode(ledRed, OUTPUT);      //menetapkan pin 9 sebagai output
}

void loop() {
int dataAnalog = analogRead (pinDigital);  //membaca nilai dari pin sensor
//print hasil ke serial monitor
Serial.print ("A0 : ");
Serial.print (dataAnalog);
lcd.setCursor(0,0);
lcd.print("Nilai: ");
lcd.setCursor(7,0);
lcd.print(dataAnalog);
//jika nilai A0 kurang dari 500, print kata serta nyalakan led hijau dan matikan led kuning, merah dan juga relay
if (dataAnalog < 500) { 
  Serial.println(". LEMBAB");
  lcd.setCursor(0,1);
  lcd.print("Lembab");
  delay(1000);
  lcd.clear(); 
  digitalWrite (ledGreen, HIGH);
  digitalWrite (ledYellow, LOW);
  digitalWrite (ledRed, LOW);
  digitalWrite (relay, HIGH);
  }

 //tetapi, jika nilai A0 kurang dari 800, print kata serta nyalakan led kuning dan relay kemudian matikan led hijau dan juga merah
 else if (dataAnalog  < 800) {
  Serial.println(". CUKUP ");
    lcd.setCursor(0,1);
  lcd.print("Cukup"); 
  delay(1000);
  lcd.clear();
  digitalWrite (ledGreen, LOW);
  digitalWrite (ledYellow, HIGH);
  digitalWrite (ledRed, LOW);
  digitalWrite (relay, HIGH);
  }

 //selain dari itu, hanya nyalakan led merah dan juga relay
 else { Serial.println (". PERLU BANYAK AIR"); 
   lcd.setCursor(0,1);
  lcd.print("Perlu Banyak Air");
  delay(1000);
  lcd.clear();
  digitalWrite (ledGreen, LOW);
  digitalWrite (ledYellow, LOW);
  digitalWrite (ledRed, HIGH);
  digitalWrite (relay, LOW);
  }


}