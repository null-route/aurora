#include "Adafruit_NeoPixel.h"
#include "pixelstruct.h"
#define PIN 6
#define TOTALPIXELS 120

Adafruit_NeoPixel strip = Adafruit_NeoPixel(TOTALPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Initialize an array of pixel structs
PixelStruct pixel[TOTALPIXELS];

// Initial setup
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

// Begin main loop
void loop() {
  breath();
}

void breath() {
  // Set random pixel color values
  struct PixelStruct tarColor;
  tarColor.r = random(1,255);
  tarColor.g = 0;
  tarColor.b = random(1,255);
  // Set target pixel location within the strip
  uint16_t targetPixelLocation = random(1, TOTALPIXELS);
  // Set target range (breadth of light spread)
  uint16_t range = random(TOTALPIXELS / 10, TOTALPIXELS / 2);
  // Start inhaling
  inhale(targetPixelLocation, range, tarColor);
  // Start exhaling
  exhale(targetPixelLocation, range, tarColor);
}

// Function for creating an 'inhale' animation.
// Color increases in intensity and breadth as a function of time.
void inhale (uint16_t targetPixelLocation, uint16_t range, PixelStruct tarColor) {
  // Set target inhale duration
  uint16_t inhaleDuration = random(10,100);
  // Set a marker to signal we're inhaling
  bool marker = true;
  // Begin inhaling for the defined duration
  for(uint16_t y=1; y<inhaleDuration; y++) {
    // Iterate through each step in the range
    for(uint16_t x=0; x<range; x++) {
      // Alternate between positive and negative values of the range
      // This could probably be more elegant
      for(uint8_t b=0; b<2; b++) {
        // If we're at the first step (the center), just use that location
        if(x == 0) {
          mutatePixel(targetPixelLocation, x, range, y, inhaleDuration, tarColor, marker);
        }
        // Selects the left pixel of the current range
        else if(b == 0) {
          mutatePixel((targetPixelLocation - x), x, range, y, inhaleDuration, tarColor, marker);
        }
        // Selects the right pixel of the current range
        else if(b == 1) {
          mutatePixel((targetPixelLocation + x), x, range, y, inhaleDuration, tarColor, marker);
        }
      }
    }
    // Update the strip after every change to the given range
    strip.show();
  }
}

// Function for creating an 'exhale' animation.
// Color decreases in intensity and breadth as a function of time.
void exhale (uint16_t targetPixelLocation, uint16_t range, PixelStruct tarColor) {
  // Set target exhale duration
  uint16_t exhaleDuration = random(10,100);
  // Set a marker to signal we're exhaling
  bool marker = false;
  // Begin exhaling for the defined duration
  for(uint16_t y=exhaleDuration; y>0; --y) {
    // Iterate through each step in the range
    for(uint16_t x=0; x<range; x++) {
      // Alternate between positive and negative values of the range
      // This could probably be more elegant
      for(uint8_t b=0; b<2; b++) {
        // If we're at the first step (the center), just use that location
        if(x == 0) {
          mutatePixel(targetPixelLocation, x, range, y, exhaleDuration, tarColor, marker);
        }
        // Selects the left pixel of the current range
        else if(b == 0) {
          mutatePixel((targetPixelLocation - x), x, range, y, exhaleDuration, tarColor, marker);
        }
        // Selects the right pixel of the current range
        else if(b == 1) {
          mutatePixel((targetPixelLocation + x), x, range, y, exhaleDuration, tarColor, marker);
        }
      }
    }
    // Update the strip after every change to the given range
    strip.show();
  }
}

// Function for mutating pixel colors based on duration, range, and target
// color values versus those currently present.
void mutatePixel(uint16_t location, uint16_t curRange, uint16_t tarRange,
uint16_t curDur, uint16_t tarDur, PixelStruct tarColor, bool marker) {
  // Check to make sure that our target is in a valid range
  if(location > 0 && location < TOTALPIXELS) {
    // Calculate modified color values based on range and duration.
    // This math may be fucked up. idklol I'm terrible at math.
    double intensity = ((double(curDur) / double(tarDur)) * (.9999 - double(curRange) / double(tarRange)));
    uint32_t calcR = (tarColor.r * intensity);
    uint32_t calcG = (tarColor.g * intensity);
    uint32_t calcB = (tarColor.b * intensity);
    // Compare calculated values to current values and replace if greater.
    // Unsure if this logic will produce the desired effect.
    // Actual testing will be required.
    if(marker) {
      if(calcR > pixel[location].r) {
        pixel[location].r = calcR;
      }
      if(calcG > pixel[location].g) {
        pixel[location].g = calcG;
      }
      if(calcB > pixel[location].b) {
        pixel[location].b = calcB;
      }
    }
    else {
      if(calcR < pixel[location].r) {
        pixel[location].r = calcR;
      }
      if(calcG < pixel[location].g) {
        pixel[location].g = calcG;
      }
      if(calcB < pixel[location].b) {
        pixel[location].b = calcB;
      }
    }
    // Set the strip's pixel color to the values of the current pixel.
    strip.setPixelColor(location, pixel[location].r, pixel[location].g, pixel[location].b);
  }
}
