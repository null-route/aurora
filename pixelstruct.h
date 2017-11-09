#ifndef pixelstruct_h
#define pixelstruct_h
#include "Arduino.h"

// Create a struct for holding pixel color values
struct PixelStruct {
  uint8_t r = 1;
  uint8_t g = 1;
  uint8_t b = 1;
  // Tell us if this pixel is blooming currently
  // This allows us to restrict writes, allowing correct behavior
  bool blooming = false;
};

// Create a struct for creating blooms
struct BloomStruct {
  // Define where the center of the bloom is located
  uint16_t center = 0;
  // Desired range/breadth of bloom
  double range = 0;
  // Define target color values for the bloom
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  // Bloom grow state and target
  double cGrow = 0;
  double tGrow = 0;
  // Bloom shrink state and target
  double cShrink = 0;
  double tShrink = 0;
  // Bloom intensity modifier
  double intensity = 0;


  // Initialize a new randomized bloom
  void initialize() {
    center = random(0, TOTALPIXELS);
    range = random(TOTALPIXELS / 10, TOTALPIXELS / 2);
    r = random(0,255);
    g = random(0,255);
    b = random(0,255);
    tGrow = random(10,100);
    cGrow = 0;
    tShrink = random(10,100);
    cShrink = tShrink;
  }
  // Advance one step through the animation
  void grow() {
    if(cGrow != tGrow) { // Begin growing the bloom to the target
      intensity = cGrow / tGrow;
      cGrow++;
    }
    else if(cShrink != 0) { // Begin shrinking the bloom to 0
      intensity = cShrink / tShrink;
      --cShrink;
    }
    else if(cGrow == tGrow && cShrink == 0) { // If bloom has completed, reinitialize
      initialize();
    }
  }
  // Apply the current bloom state to the pixel array
  void apply(PixelStruct arr[]) {


    double intensity = ((double(curDur) / double(tarDur)) * (.9999 - double(curRange) / double(tarRange)));

    for(uint16_t x=0; x<range; x++) {
      // Alternate between positive and negative values of the range
      // This could probably be more elegant
      arr[center - x]
      arr[center + x]








      for(uint8_t b=0; b<2; b++) {
        // If we're at the first step (the center), just use that location
        if(x == 0) {
          arr[center]
          mutatePixel(center, x, range, y, exhaleDuration, tarColor, marker);
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
  }
}

#endif
