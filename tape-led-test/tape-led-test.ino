#include <FastLED.h>

#define NUM_LEDS   60
#define BRIGHTNESS 5
#define LED_TYPE   WS2812B
#define DATA_PIN   21
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  
}

void loop() {

  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(10);
  }
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Blue;
    FastLED.show();
    delay(10);
  }
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Green;
    FastLED.show();
    delay(10);
  }
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB::White;
    FastLED.show();
    delay(10);
  }
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB(228, 0, 127); 
    FastLED.show();
    delay(10);
  }
  for(int j=0; j<NUM_LEDS; j++){
    leds[j] = CRGB::Black;
    FastLED.show();
    delay(10);
  }
  delay(500);
}
