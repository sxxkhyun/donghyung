#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define PIN D2
#define NUM_LEDS 16

char *ssid = "Kangdonghyung";
char *password = "1234567890";
int data = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println();
  Serial.println("WiFi connected.");
}

void loop() {

  HTTPClient httpClient;
  String host = "http://api.openweathermap.org";
  String url = "/data/2.5/weather?id=1832828&appid=";
  String key = "24b1d7c7237a494da40376f4cbeba610";

  httpClient.begin(host + url + key);
  int httpCode = httpClient.GET();

  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = httpClient.getString();
      processWeatherInformation(payload);
    }
  } else {
    
  }

  httpClient.end();

  delay(5000);
}

void processWeatherInformation(String buffer) {
  int index1, index2;
  String fieldInfo;
  char *key1 = "\"weather\"", *key2 = "\"main\"", *key3 = "\"temp\"", *key4 = "\"id\"";

  //weather.main
  index1 = buffer.indexOf(key1);
  index2 = buffer.indexOf(key2, index1);
  index1 = buffer.indexOf('\"', index2 + strlen(key2));
  index2 = buffer.indexOf('\"', index1 + 1);

  fieldInfo = buffer.substring(index1 + 1, index2);

  lcd.setCursor(0, 0);
  lcd.print("Yangsan :");
  lcd.print(fieldInfo);

  //main.temp
  index1 = buffer.indexOf(key3, index2);
  index2 = buffer.indexOf(':', index1 + strlen(key3));
  index1 = buffer.indexOf(',', index2 + 1);

  fieldInfo = buffer.substring(index2 + 1, index1);
  float temperature = fieldInfo.toFloat() - 273.15;


  //weather.main.id
  index1 = buffer.indexOf(key4);
  index2 = buffer.indexOf(key2, index1);
  index2 = buffer.indexOf(':', index1 + strlen(key4));
  index1 = buffer.indexOf(',', index2 + 1);

  fieldInfo = buffer.substring(index2 + 1, index1);
  int id = fieldInfo.toFloat();

  if (id == 800)
  {
    id = 1;
    Serial.print(id);
    Serial.println();
  }
  else if (id > 950) {
    id = 4;
    Serial.print(id);
    Serial.println();
  }
  else {
    id = id / 100;
    Serial.print(id);
    Serial.println();
  }
  delay(1000);

  lcd.setCursor(0, 1);
  lcd.print("Temp    :");
  lcd.print(temperature);
  lcd.print(char(223));
  lcd.print("C ");

}
