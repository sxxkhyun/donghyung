#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define PIN 4
#define NUM_LEDS 16
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

DHT dht(DHTPIN, DHTTYPE);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27, 16, 2);


int buzzer = 3;
int tones[] = {NOTE_E5, 8, NOTE_E5, 8, REST, 8, NOTE_E5, 8, REST, 8, NOTE_C5, 8, NOTE_E5, 8, //1
               NOTE_G5, 4, REST, 4, NOTE_G4, 8, REST, 4,
               NOTE_C5, -4, NOTE_G4, 8, REST, 4, NOTE_E4, -4, // 3
               NOTE_A4, 4, NOTE_B4, 4, NOTE_AS4, 8, NOTE_A4, 4,
               NOTE_G4, -8, NOTE_E5, -8, NOTE_G5, -8, NOTE_A5, 4, NOTE_F5, 8, NOTE_G5, 8,
               REST, 8, NOTE_E5, 4, NOTE_C5, 8, NOTE_D5, 8, NOTE_B4, -4,
               NOTE_C5, -4, NOTE_G4, 8, REST, 4, NOTE_E4, -4, // repeats from 3
               NOTE_A4, 4, NOTE_B4, 4, NOTE_AS4, 8, NOTE_A4, 4,
               REST, 4, NOTE_G5, 8, NOTE_FS5, 8, NOTE_F5, 8, NOTE_DS5, 4, NOTE_E5, 8, //7
               REST, 8, NOTE_GS4, 8, NOTE_A4, 8, NOTE_C4, 8, REST, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_D5, 8,
               REST, 4, NOTE_DS5, 4, REST, 8, NOTE_D5, -4,
               NOTE_C5, 2, REST, 2,
              };
int tempo = 320;
int notes = sizeof(tones) / sizeof(tones[0]) / 2;
int divider = 0, noteDuration = 0;
int wholenote = (60000 * 4) / tempo;

void setup() {
  Serial.begin(115200);
  Serial.println("DHT22 begin!");
  dht.begin();
  lcd.init();
  lcd.backlight();
  strip.begin();
  strip.show();
  pinMode (buzzer, OUTPUT);
}

void loop() {

  delay(2000);
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


    if (Temp < 15) {
      if (RH < 70) {
        Serial.println("It's dry. Please turn on the humidifier");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("It's dry");
        lcd.setCursor(0, 1);
        lcd.print("Turn humidifier");
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
          divider = tones[thisNote + 1];
          if (divider > 0) {

            noteDuration = (wholenote) / divider;
          } else if (divider < 0) {

            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5;
          }
          tone(buzzer, tones[thisNote], noteDuration * 0.9);
          delay(noteDuration);
          noTone(buzzer);
        }
        delay(1000);
        return;
      }
    }


    if (Temp > 18 || Temp < 20) {
      if (RH < 60) {
        Serial.println("It's dry. Please turn on the humidifier");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("It's dry");
        lcd.setCursor(0, 1);
        lcd.print("Turn humidifier");
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
          divider = tones[thisNote + 1];
          if (divider > 0) {

            noteDuration = (wholenote) / divider;
          } else if (divider < 0) {

            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5;
          }
          tone(buzzer, tones[thisNote], noteDuration * 0.9);
          delay(noteDuration);
          noTone(buzzer);
        }

        delay(1000);
        return;
      }
    }

    if (Temp > 21 || Temp < 23) {
      if (RH < 50) {
        Serial.println("It's dry. Please turn on the humidifier");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("It's dry");
        lcd.setCursor(0, 1);
        lcd.print("Turn humidifier");
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
          divider = tones[thisNote + 1];
          if (divider > 0) {

            noteDuration = (wholenote) / divider;
          } else if (divider < 0) {

            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5;
          }
          tone(buzzer, tones[thisNote], noteDuration * 0.9);
          delay(noteDuration);
          noTone(buzzer);
        }
        delay(1000);
        return;
      }
    }


    if (Temp > 24) {
      if (RH < 40) {
        Serial.println("It's dry. Please turn on the humidifier");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("It's dry");
        lcd.setCursor(0, 1);
        lcd.print("Turn humidifier");
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
          divider = tones[thisNote + 1];
          if (divider > 0) {

            noteDuration = (wholenote) / divider;
          } else if (divider < 0) {

            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5;
          }
          tone(buzzer, tones[thisNote], noteDuration * 0.9);
          delay(noteDuration);
          noTone(buzzer);
        }
        delay(1000);
        return;
      }

    }
  }
}
