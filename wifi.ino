finclude <ESP8266WiFi.h>b
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const char* ssid = "your-wifi-address";  //SSID of local network
const char* password = "your-wifi-password";          //Password on network
String APIKEY = "ed0bb8fea7adde1002048891b9f31d23";
String CityID = "745044";                     //Istanbul City ID
char servername[] = "api.openweathermap.org"; //Remote server we will connect to 
String result;
int counter = 60;
String weatherForecast = "";
String weatherMyLocation = "";
float temp;

WifiClient client;
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  Serial.begin(115200);
  int cursorPositon = 0;
  lcd.begin();
  lcd.backlight();
  lcd.print("Please Wait");
  Wifi.begin(ssid, password); //wifi start

  while(Wifi.status() != WL_CONNECTED){
    delay(500);
    lcd.setCursor(cursorPosition,2);
    lcd.print(".");
    cursorPosition++;
  }
  lcd.clear();
  lcd.print(" Connected");
  delay(1000);
}

void loop() {
  if(counter == 60){
    counter = 0;
    getWeatherData();
  }
  else{
    counter ++ ;
    displayConditions(temp, weatherMyLocation, weatherForecast);
    delay(2000);
  }
}
