#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include <DHT.h>

#define LED_PIN      3
#define NUM_LEDS     16

#define DHTPIN       2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 begin!");
  dht.begin();
  lcd.init();
  lcd.backlight();
  strip.begin();
  strip.show();
}

void loop() {

  if (Serial.available()) { // 데이터 수신 확인
    char ch = Serial.read(); // 1 바이트 데이터 읽기
    Serial.write(Serial.read());

    if (ch == '1') {
      for (int i = 0 ; i < 16 ; i++) {
        strip.setPixelColor(i, 15, 76, 129); //Classic Blue - Clear
        strip.show();
      }
      float RH = dht.readHumidity();
      float Temp = dht.readTemperature();
      float AH = dht.computeHeatIndex(Temp, RH, false);
      float WTemp = Temp * atan(0.151977 * pow(RH + 8.313659, 0.5)) + atan(Temp + RH) - atan(RH - 1.676331) + 0.003918 * pow(RH, 1.5) * atan(0.023101 * RH) - 4.686035;
      float DewPoint = Temp - ((14.55 + 0.114 * Temp) * (1. - 0.01 * RH) + pow((2.5 + 0.007 * Temp) * (1. - 0.01 * RH), 3) + (15.9 + 0.117 * Temp) * pow((1. - 0.01 * RH), 14));
      float DI = 0.72 * (Temp + WTemp) + 40.6;

      if (isnan(RH) || isnan(Temp)) {
        Serial.println("** Error in reading DHT sensor!");
        return;
      }

      else {
        Serial.print("* Temperature (℃) = ");
        Serial.println(Temp, 1);
        Serial.print("* Relative Humidity (%) = ");
        Serial.println(RH, 1);
        Serial.print("* Absolute Humidity (g/m3) = ");
        Serial.println(AH, 1);
        Serial.print("* Wet-bulb Temperature (℃) = ");
        Serial.println(WTemp, 1);
        Serial.print("* Dew-point Temperature (℃) = ");
        Serial.println(DewPoint, 1);
        Serial.print("* Discomfort Index = ");
        Serial.println(DI, 1);
        Serial.println("------------------------------------");

      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp   :");
      lcd.print(Temp);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Hdt    :");
      lcd.print(RH);
      lcd.println("%  ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("AHdt  :");
      lcd.print(AH);
      lcd.print("g/m3");
      lcd.setCursor(0, 1);
      lcd.print("WTemp :");
      lcd.print(WTemp);
      lcd.print(char(223));
      lcd.print("C ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DewPoint:");
      lcd.print(DewPoint);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Discomfort:");
      lcd.print(DI);
      delay(2000);

    }
    
    else if (ch == '2') {
      for (int i = 0 ; i < 16 ; i++) {
        strip.setPixelColor(i, 255, 111, 97); // Living Coral - Thunderstorm
        strip.show();
      }
      float RH = dht.readHumidity();
      float Temp = dht.readTemperature();
      float AH = dht.computeHeatIndex(Temp, RH, false);
      float WTemp = Temp * atan(0.151977 * pow(RH + 8.313659, 0.5)) + atan(Temp + RH) - atan(RH - 1.676331) + 0.003918 * pow(RH, 1.5) * atan(0.023101 * RH) - 4.686035;
      float DewPoint = Temp - ((14.55 + 0.114 * Temp) * (1. - 0.01 * RH) + pow((2.5 + 0.007 * Temp) * (1. - 0.01 * RH), 3) + (15.9 + 0.117 * Temp) * pow((1. - 0.01 * RH), 14));
      float DI = 0.72 * (Temp + WTemp) + 40.6;

      if (isnan(RH) || isnan(Temp)) {
        Serial.println("** Error in reading DHT sensor!");
        return;
      }

      else {
        Serial.print("* Temperature (℃) = ");
        Serial.println(Temp, 1);
        Serial.print("* Relative Humidity (%) = ");
        Serial.println(RH, 1);
        Serial.print("* Absolute Humidity (g/m3) = ");
        Serial.println(AH, 1);
        Serial.print("* Wet-bulb Temperature (℃) = ");
        Serial.println(WTemp, 1);
        Serial.print("* Dew-point Temperature (℃) = ");
        Serial.println(DewPoint, 1);
        Serial.print("* Discomfort Index = ");
        Serial.println(DI, 1);
        Serial.println("------------------------------------");
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp   :");
      lcd.print(Temp);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Hdt    :");
      lcd.print(RH);
      lcd.println("%  ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("AHdt  :");
      lcd.print(AH);
      lcd.print("g/m3");
      lcd.setCursor(0, 1);
      lcd.print("WTemp :");
      lcd.print(WTemp);
      lcd.print(char(223));
      lcd.print("C ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DewPoint:");
      lcd.print(DewPoint);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Discomfort:");
      lcd.print(DI);
      delay(2000);

    }

    else if (ch == '3') {
      for (int i = 0 ; i < 16 ; i++) {
        strip.setPixelColor(i, 127, 201, 203); //Aqua Sky - Drizzle
        strip.show();
      }
      float RH = dht.readHumidity();
      float Temp = dht.readTemperature();
      float AH = dht.computeHeatIndex(Temp, RH, false);
      float WTemp = Temp * atan(0.151977 * pow(RH + 8.313659, 0.5)) + atan(Temp + RH) - atan(RH - 1.676331) + 0.003918 * pow(RH, 1.5) * atan(0.023101 * RH) - 4.686035;
      float DewPoint = Temp - ((14.55 + 0.114 * Temp) * (1. - 0.01 * RH) + pow((2.5 + 0.007 * Temp) * (1. - 0.01 * RH), 3) + (15.9 + 0.117 * Temp) * pow((1. - 0.01 * RH), 14));
      float DI = 0.72 * (Temp + WTemp) + 40.6;

      if (isnan(RH) || isnan(Temp)) {
        Serial.println("** Error in reading DHT sensor!");
        return;
      }

      else {
        Serial.print("* Temperature (℃) = ");
        Serial.println(Temp, 1);
        Serial.print("* Relative Humidity (%) = ");
        Serial.println(RH, 1);
        Serial.print("* Absolute Humidity (g/m3) = ");
        Serial.println(AH, 1);
        Serial.print("* Wet-bulb Temperature (℃) = ");
        Serial.println(WTemp, 1);
        Serial.print("* Dew-point Temperature (℃) = ");
        Serial.println(DewPoint, 1);
        Serial.print("* Discomfort Index = ");
        Serial.println(DI, 1);
        Serial.println("------------------------------------");

      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp   :");
      lcd.print(Temp);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Hdt    :");
      lcd.print(RH);
      lcd.println("%  ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("AHdt  :");
      lcd.print(AH);
      lcd.print("g/m3");
      lcd.setCursor(0, 1);
      lcd.print("WTemp :");
      lcd.print(WTemp);
      lcd.print(char(223));
      lcd.print("C ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DewPoint:");
      lcd.print(DewPoint);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Discomfort:");
      lcd.print(DI);
      delay(2000);

    }
    
    else if (ch == '4') {
      for (int i = 0 ; i < 16 ; i++) {
        strip.setPixelColor(i, 136, 176, 75); //Greenery - Additional
        strip.show();
      }
      float RH = dht.readHumidity();
      float Temp = dht.readTemperature();
      float AH = dht.computeHeatIndex(Temp, RH, false);
      float WTemp = Temp * atan(0.151977 * pow(RH + 8.313659, 0.5)) + atan(Temp + RH) - atan(RH - 1.676331) + 0.003918 * pow(RH, 1.5) * atan(0.023101 * RH) - 4.686035;
      float DewPoint = Temp - ((14.55 + 0.114 * Temp) * (1. - 0.01 * RH) + pow((2.5 + 0.007 * Temp) * (1. - 0.01 * RH), 3) + (15.9 + 0.117 * Temp) * pow((1. - 0.01 * RH), 14));
      float DI = 0.72 * (Temp + WTemp) + 40.6;

      if (isnan(RH) || isnan(Temp)) {
        Serial.println("** Error in reading DHT sensor!");
        return;
      }

      else {
        Serial.print("* Temperature (℃) = ");
        Serial.println(Temp, 1);
        Serial.print("* Relative Humidity (%) = ");
        Serial.println(RH, 1);
        Serial.print("* Absolute Humidity (g/m3) = ");
        Serial.println(AH, 1);
        Serial.print("* Wet-bulb Temperature (℃) = ");
        Serial.println(WTemp, 1);
        Serial.print("* Dew-point Temperature (℃) = ");
        Serial.println(DewPoint, 1);
        Serial.print("* Discomfort Index = ");
        Serial.println(DI, 1);
        Serial.println("------------------------------------");
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp   :");
      lcd.print(Temp);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Hdt    :");
      lcd.print(RH);
      lcd.println("%  ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("AHdt  :");
      lcd.print(AH);
      lcd.print("g/m3");
      lcd.setCursor(0, 1);
      lcd.print("WTemp :");
      lcd.print(WTemp);
      lcd.print(char(223));
      lcd.print("C ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DewPoint:");
      lcd.print(DewPoint);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Discomfort:");
      lcd.print(DI);
      delay(2000);

    }
    
    else if (ch == '5') {
      for (int i = 0 ; i < 16 ; i++) {
        strip.setPixelColor(i, 95, 75, 139); //Ultra violet - Rain
        strip.show();
      }
      float RH = dht.readHumidity();
      float Temp = dht.readTemperature();
      float AH = dht.computeHeatIndex(Temp, RH, false);
      float WTemp = Temp * atan(0.151977 * pow(RH + 8.313659, 0.5)) + atan(Temp + RH) - atan(RH - 1.676331) + 0.003918 * pow(RH, 1.5) * atan(0.023101 * RH) - 4.686035;
      float DewPoint = Temp - ((14.55 + 0.114 * Temp) * (1. - 0.01 * RH) + pow((2.5 + 0.007 * Temp) * (1. - 0.01 * RH), 3) + (15.9 + 0.117 * Temp) * pow((1. - 0.01 * RH), 14));
      float DI = 0.72 * (Temp + WTemp) + 40.6;

      if (isnan(RH) || isnan(Temp)) {
        Serial.println("** Error in reading DHT sensor!");
        return;
      }

      else {
        Serial.print("* Temperature (℃) = ");
        Serial.println(Temp, 1);
        Serial.print("* Relative Humidity (%) = ");
        Serial.println(RH, 1);
        Serial.print("* Absolute Humidity (g/m3) = ");
        Serial.println(AH, 1);
        Serial.print("* Wet-bulb Temperature (℃) = ");
        Serial.println(WTemp, 1);
        Serial.print("* Dew-point Temperature (℃) = ");
        Serial.println(DewPoint, 1);
        Serial.print("* Discomfort Index = ");
        Serial.println(DI, 1);
        Serial.println("------------------------------------");
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp   :");
      lcd.print(Temp);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Hdt    :");
      lcd.print(RH);
      lcd.println("%  ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("AHdt  :");
      lcd.print(AH);
      lcd.print("g/m3");
      lcd.setCursor(0, 1);
      lcd.print("WTemp :");
      lcd.print(WTemp);
      lcd.print(char(223));
      lcd.print("C ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DewPoint:");
      lcd.print(DewPoint);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Discomfort:");
      lcd.print(DI);
      delay(2000);

    }
    
    else if (ch == '6') {
      for (int i = 0 ; i < 16 ; i++) {
        strip.setPixelColor(i, 222, 206, 187); //Sand Dollar - Snow
        strip.show();
      }
      float RH = dht.readHumidity();
      float Temp = dht.readTemperature();
      float AH = dht.computeHeatIndex(Temp, RH, false);
      float WTemp = Temp * atan(0.151977 * pow(RH + 8.313659, 0.5)) + atan(Temp + RH) - atan(RH - 1.676331) + 0.003918 * pow(RH, 1.5) * atan(0.023101 * RH) - 4.686035;
      float DewPoint = Temp - ((14.55 + 0.114 * Temp) * (1. - 0.01 * RH) + pow((2.5 + 0.007 * Temp) * (1. - 0.01 * RH), 3) + (15.9 + 0.117 * Temp) * pow((1. - 0.01 * RH), 14));
      float DI = 0.72 * (Temp + WTemp) + 40.6;

      if (isnan(RH) || isnan(Temp)) {
        Serial.println("** Error in reading DHT sensor!");
        return;
      }

      else {
        Serial.print("* Temperature (℃) = ");
        Serial.println(Temp, 1);
        Serial.print("* Relative Humidity (%) = ");
        Serial.println(RH, 1);
        Serial.print("* Absolute Humidity (g/m3) = ");
        Serial.println(AH, 1);
        Serial.print("* Wet-bulb Temperature (℃) = ");
        Serial.println(WTemp, 1);
        Serial.print("* Dew-point Temperature (℃) = ");
        Serial.println(DewPoint, 1);
        Serial.print("* Discomfort Index = ");
        Serial.println(DI, 1);
        Serial.println("------------------------------------");
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp   :");
      lcd.print(Temp);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Hdt    :");
      lcd.print(RH);
      lcd.println("%  ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("AHdt  :");
      lcd.print(AH);
      lcd.print("g/m3");
      lcd.setCursor(0, 1);
      lcd.print("WTemp :");
      lcd.print(WTemp);
      lcd.print(char(223));
      lcd.print("C ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DewPoint:");
      lcd.print(DewPoint);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Discomfort:");
      lcd.print(DI);
      delay(2000);

    }
    
    else if (ch == '7') {
      for (int i = 0 ; i < 16 ; i++) {
        strip.setPixelColor(i, 248, 205, 205); //Rose Quartz - Atmosphere
        strip.show();
      }
      float RH = dht.readHumidity();
      float Temp = dht.readTemperature();
      float AH = dht.computeHeatIndex(Temp, RH, false);
      float WTemp = Temp * atan(0.151977 * pow(RH + 8.313659, 0.5)) + atan(Temp + RH) - atan(RH - 1.676331) + 0.003918 * pow(RH, 1.5) * atan(0.023101 * RH) - 4.686035;
      float DewPoint = Temp - ((14.55 + 0.114 * Temp) * (1. - 0.01 * RH) + pow((2.5 + 0.007 * Temp) * (1. - 0.01 * RH), 3) + (15.9 + 0.117 * Temp) * pow((1. - 0.01 * RH), 14));
      float DI = 0.72 * (Temp + WTemp) + 40.6;

      if (isnan(RH) || isnan(Temp)) {
        Serial.println("** Error in reading DHT sensor!");
        return;
      }

      else {
        Serial.print("* Temperature (℃) = ");
        Serial.println(Temp, 1);
        Serial.print("* Relative Humidity (%) = ");
        Serial.println(RH, 1);
        Serial.print("* Absolute Humidity (g/m3) = ");
        Serial.println(AH, 1);
        Serial.print("* Wet-bulb Temperature (℃) = ");
        Serial.println(WTemp, 1);
        Serial.print("* Dew-point Temperature (℃) = ");
        Serial.println(DewPoint, 1);
        Serial.print("* Discomfort Index = ");
        Serial.println(DI, 1);
        Serial.println("------------------------------------");
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp   :");
      lcd.print(Temp);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Hdt    :");
      lcd.print(RH);
      lcd.println("%  ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("AHdt  :");
      lcd.print(AH);
      lcd.print("g/m3");
      lcd.setCursor(0, 1);
      lcd.print("WTemp :");
      lcd.print(WTemp);
      lcd.print(char(223));
      lcd.print("C ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DewPoint:");
      lcd.print(DewPoint);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Discomfort:");
      lcd.print(DI);
      delay(2000);

    }
    
    else if (ch == '8') {
      for (int i = 0 ; i < 16 ; i++) {
        strip.setPixelColor(i, 176, 205, 223); //Serenity - Clouds
        strip.show();
      }
      float RH = dht.readHumidity();
      float Temp = dht.readTemperature();
      float AH = dht.computeHeatIndex(Temp, RH, false);
      float WTemp = Temp * atan(0.151977 * pow(RH + 8.313659, 0.5)) + atan(Temp + RH) - atan(RH - 1.676331) + 0.003918 * pow(RH, 1.5) * atan(0.023101 * RH) - 4.686035;
      float DewPoint = Temp - ((14.55 + 0.114 * Temp) * (1. - 0.01 * RH) + pow((2.5 + 0.007 * Temp) * (1. - 0.01 * RH), 3) + (15.9 + 0.117 * Temp) * pow((1. - 0.01 * RH), 14));
      float DI = 0.72 * (Temp + WTemp) + 40.6;

      if (isnan(RH) || isnan(Temp)) {
        Serial.println("** Error in reading DHT sensor!");
        return;
      }

      else {
        Serial.print("* Temperature (℃) = ");
        Serial.println(Temp, 1);
        Serial.print("* Relative Humidity (%) = ");
        Serial.println(RH, 1);
        Serial.print("* Absolute Humidity (g/m3) = ");
        Serial.println(AH, 1);
        Serial.print("* Wet-bulb Temperature (℃) = ");
        Serial.println(WTemp, 1);
        Serial.print("* Dew-point Temperature (℃) = ");
        Serial.println(DewPoint, 1);
        Serial.print("* Discomfort Index = ");
        Serial.println(DI, 1);
        Serial.println("------------------------------------");
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp   :");
      lcd.print(Temp);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Hdt    :");
      lcd.print(RH);
      lcd.println("%  ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("AHdt  :");
      lcd.print(AH);
      lcd.print("g/m3");
      lcd.setCursor(0, 1);
      lcd.print("WTemp :");
      lcd.print(WTemp);
      lcd.print(char(223));
      lcd.print("C ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DewPoint:");
      lcd.print(DewPoint);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Discomfort:");
      lcd.print(DI);
      delay(2000);

    }
    
    else if (ch == '9') {
      for (int i = 0 ; i < 16 ; i++) {
        strip.setPixelColor(i, 151, 90, 88); //Marsala - Extreme
        strip.show();
      }
      float RH = dht.readHumidity();
      float Temp = dht.readTemperature();
      float AH = dht.computeHeatIndex(Temp, RH, false);
      float WTemp = Temp * atan(0.151977 * pow(RH + 8.313659, 0.5)) + atan(Temp + RH) - atan(RH - 1.676331) + 0.003918 * pow(RH, 1.5) * atan(0.023101 * RH) - 4.686035;
      float DewPoint = Temp - ((14.55 + 0.114 * Temp) * (1. - 0.01 * RH) + pow((2.5 + 0.007 * Temp) * (1. - 0.01 * RH), 3) + (15.9 + 0.117 * Temp) * pow((1. - 0.01 * RH), 14));
      float DI = 0.72 * (Temp + WTemp) + 40.6;

      if (isnan(RH) || isnan(Temp)) {
        Serial.println("** Error in reading DHT sensor!");
        return;
      }

      else {
        Serial.print("* Temperature (℃) = ");
        Serial.println(Temp, 1);
        Serial.print("* Relative Humidity (%) = ");
        Serial.println(RH, 1);
        Serial.print("* Absolute Humidity (g/m3) = ");
        Serial.println(AH, 1);
        Serial.print("* Wet-bulb Temperature (℃) = ");
        Serial.println(WTemp, 1);
        Serial.print("* Dew-point Temperature (℃) = ");
        Serial.println(DewPoint, 1);
        Serial.print("* Discomfort Index = ");
        Serial.println(DI, 1);
        Serial.println("------------------------------------");
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp   :");
      lcd.print(Temp);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Hdt    :");
      lcd.print(RH);
      lcd.println("%  ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("AHdt  :");
      lcd.print(AH);
      lcd.print("g/m3");
      lcd.setCursor(0, 1);
      lcd.print("WTemp :");
      lcd.print(WTemp);
      lcd.print(char(223));
      lcd.print("C ");
      delay(2000);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DewPoint:");
      lcd.print(DewPoint);
      lcd.print(char(223));
      lcd.print("C ");
      lcd.setCursor(0, 1);
      lcd.print("Discomfort:");
      lcd.print(DI);
      delay(2000);

    }
  }

}
