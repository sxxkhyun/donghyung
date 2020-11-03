#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

#define PIN 5  
#define NUM_LEDS 16

char *ssid = "Home";
char *password = "0517018451";

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  lcd.init();
  lcd.backlight();
  strip.begin();
  strip.show();

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  Serial.print("Connecting to \'");
  Serial.print(ssid);
  Serial.println("\'");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
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
    Serial.printf("[HTTP] request from the client was handled : %d\n", httpCode);

    if (httpCode == HTTP_CODE_OK) {
      String payload = httpClient.getString();
      processWeatherInformation(payload);
    }
  } else {
    Serial.printf("[HTTP] connection failed : %s\n", httpClient.errorToString(httpCode).c_str());
  }

  httpClient.end();

  delay(5000);
}

void processWeatherInformation(String buffer) {
  int index1, index2;
  String fieldInfo;
  char *key1 = "\"weather\"", *key2 = "\"main\"", *key3 = "\"temp\"";

  index1 = buffer.indexOf(key1);
  index2 = buffer.indexOf(key2, index1);
  index1 = buffer.indexOf('\"', index2 + strlen(key2));
  index2 = buffer.indexOf('\"', index1 + 1);

  fieldInfo = buffer.substring(index1 + 1, index2);
  Serial.println();
  Serial.println("Current Weather in Yangsan  : " + fieldInfo);
  lcd.setCursor(0, 0);
  lcd.print("Yangsan :");
  lcd.print(fieldInfo);

  index1 = buffer.indexOf(key3, index2);
  index2 = buffer.indexOf(':', index1 + strlen(key3));
  index1 = buffer.indexOf(',', index2 + 1);

  fieldInfo = buffer.substring(index2 + 1, index1);
  float temperature = fieldInfo.toFloat() - 273.15;
  Serial.print("Current Temperature in Yangsan :  ");
  Serial.println(temperature);
  Serial.println();
  lcd.setCursor(0, 1);
  lcd.print("Temper  :");
  lcd.print(temperature);
  lcd.print(char(223));
  lcd.print("C ");

  if (fieldInfo == "Clear")
  strip.setPixelColor(0, 255, 0, 0);
}
