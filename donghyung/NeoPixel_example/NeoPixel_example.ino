#include <Adafruit_NeoPixel.h>
//define NeoPixel Pin and Number of LEDs
#define PIN 5  
#define NUM_LEDS 16

//create a NeoPixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);



void setup() {

  // start the strip and blank it out
  strip.begin();
  strip.show();

}



void loop() {

  // set pixel to red, delay(1000)

  strip.setPixelColor(0, 255, 0, 0);
  strip.setPixelColor(1, 255, 0, 0);
  strip.setPixelColor(2, 255, 0, 0);
  strip.setPixelColor(3, 255, 0, 0);
  strip.setPixelColor(4, 80, 188, 223);
  strip.setPixelColor(5, 80, 188, 223);
  strip.setPixelColor(6, 80, 188, 223);
  strip.setPixelColor(7, 80, 188, 223);
  strip.setPixelColor(8, 236, 230, 204);
  strip.setPixelColor(9, 236, 230, 204);
  strip.setPixelColor(10, 236, 230, 204);
  strip.setPixelColor(11, 236, 230, 204);
  strip.setPixelColor(12, 51, 52, 57);
  strip.setPixelColor(13, 51, 52, 57);
  strip.setPixelColor(14, 51, 52, 57);
  strip.setPixelColor(15, 51, 52, 57);
  
  strip.show();
  delay(1000);


}
