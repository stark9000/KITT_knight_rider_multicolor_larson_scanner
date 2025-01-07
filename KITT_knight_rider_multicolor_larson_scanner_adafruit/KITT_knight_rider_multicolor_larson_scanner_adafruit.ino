#include <Adafruit_NeoPixel.h>

#define LED_PIN PB2
#define POT_PIN PB3
#define NUM_LEDS 16

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t colors[] = {
  strip.Color(255, 0, 255),    // Magenta
  strip.Color(255, 165, 0),    // Orange
  strip.Color(128, 0, 128),    // Purple
  strip.Color(0, 128, 0),      // Dark Green
  strip.Color(128, 128, 0),    // Olive
  strip.Color(0, 128, 128),    // Teal
  strip.Color(128, 0, 0),      // Maroon
  strip.Color(0, 0, 128),      // Navy
  strip.Color(192, 192, 192),  // Silver
  strip.Color(128, 128, 128),  // Gray
  strip.Color(255, 20, 147),   // Deep Pink
  strip.Color(135, 206, 235),  // Sky Blue
  strip.Color(75, 0, 130),     // Indigo
  strip.Color(240, 230, 140),  // Khaki
  strip.Color(173, 216, 230),  // Light Blue
  strip.Color(255, 105, 180)   // Hot Pink
};

int numColors = sizeof(colors) / sizeof(colors[0]);
int currentColorIndex = 0;
int POT_SPEED;
int SPEED;

bool directionForward = true;
int position = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  POT_SPEED = analogRead(POT_PIN);
  SPEED = map(POT_SPEED, 0, 1023, 20, 400);

  // Fade all LEDs
  fadeToBlackBy(strip, 80);

  // Set the current position to the current color
  strip.setPixelColor(position, colors[currentColorIndex]);

  // Update position
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

  strip.show();
  delay(SPEED);
}

void fadeToBlackBy(Adafruit_NeoPixel &strip, uint8_t fadeFactor) {
  for (int i = 0; i < strip.numPixels(); i++) {
    uint32_t color = strip.getPixelColor(i);

    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    // Scale down RGB values by fadeFactor
    r = r * (255 - fadeFactor) / 255;
    g = g * (255 - fadeFactor) / 255;
    b = b * (255 - fadeFactor) / 255;

    // Set the pixel with faded color
    strip.setPixelColor(i, r, g, b);
  }
}
