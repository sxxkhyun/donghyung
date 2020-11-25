#include <Adafruit_NeoPixel.h>
#define PIN 2
#define NUM_LEDS 16

//create a NeoPixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  strip.begin();
  strip.show();

}



void loop() {

  for (int i = 0 ; i < 16 ; i++) {
    strip.setPixelColor(i, 255, 111, 97); // Living Coral - Thunderstorm
    strip.show();
  }
  delay(1000);
  for (int i = 0 ; i < 16 ; i++) {
    strip.setPixelColor(i, 127, 201, 203); //Aqua Sky - Drizzle
    strip.show();
  }
  delay(1000);
  for (int i = 0 ; i < 16 ; i++) {
    strip.setPixelColor(i, 95, 75, 139); //Ultra violet - Rain
    strip.show();
  }
  delay(1000);
  for (int i = 0 ; i < 16 ; i++) {
    strip.setPixelColor(i, 222, 206, 187); //Sand Dollar - Snow
    strip.show();
  }
  delay(1000);
  for (int i = 0 ; i < 16 ; i++) {
    strip.setPixelColor(i, 248, 205, 205); //Rose Quartz - Atmosphere
    strip.show();
  }
  delay(1000);
  for (int i = 0 ; i < 16 ; i++) {
    strip.setPixelColor(i, 15, 76, 129); //Classic Blue - Clear
    strip.show();
  }
  delay(1000);
  for (int i = 0 ; i < 16 ; i++) {
    strip.setPixelColor(i, 176, 205, 223); //Serenity - Clouds
    strip.show();
  }
  delay(1000);
  for (int i = 0 ; i < 16 ; i++) {
    strip.setPixelColor(i, 151, 90, 88); //Marsala - Extreme
    strip.show();
  }
  delay(1000);
  for (int i = 0 ; i < 16 ; i++) {
    strip.setPixelColor(i, 136, 176, 75); //Greenery - Additional
    strip.show();
  }
  delay(1000);
}
