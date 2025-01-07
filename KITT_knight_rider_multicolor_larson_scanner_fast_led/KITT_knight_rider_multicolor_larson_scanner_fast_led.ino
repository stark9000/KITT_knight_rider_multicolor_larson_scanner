#include <FastLED.h>

#define LED_PIN PB2
#define POT_PIN PB3
#define NUM_LEDS 16

CRGB leds[NUM_LEDS];

CRGB colors[] = {
  CRGB(255, 0, 255),    // Magenta
  CRGB(255, 165, 0),    // Orange
  CRGB(128, 0, 128),    // Purple
  CRGB(0, 128, 0),      // Dark Green
  CRGB(128, 128, 0),    // Olive
  CRGB(0, 128, 128),    // Teal
  CRGB(128, 0, 0),      // Maroon
  CRGB(0, 0, 128),      // Navy
  CRGB(192, 192, 192),  // Silver
  CRGB(128, 128, 128),  // Gray
  CRGB(255, 20, 147),   // Deep Pink
  CRGB(135, 206, 235),  // Sky Blue
  CRGB(75, 0, 130),     // Indigo
  CRGB(240, 230, 140),  // Khaki
  CRGB(173, 216, 230),  // Light Blue
  CRGB(255, 105, 180)   // Hot Pink
};

int numColors = sizeof(colors) / sizeof(colors[0]);
int currentColorIndex = 0;
int POT_SPEED;
int SPEED;

bool directionForward = true;
int position = 0;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
}

void loop() {
  POT_SPEED = analogRead(POT_PIN);
  SPEED = map(POT_SPEED, 0, 1023, 20, 400);

  fadeToBlackBy(leds, NUM_LEDS, 50);// TAIL ADJUST
  leds[position] = colors[currentColorIndex];
  if (directionForward) {
    position++;
    if (position >= NUM_LEDS - 1) {
      directionForward = false;
    }
  } else {
    position--;
    if (position <= 0) {
      directionForward = true;
      currentColorIndex = (currentColorIndex + 1) % numColors;
    }
  }
  FastLED.show();
  FastLED.delay(SPEED);

}
