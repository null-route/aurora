#ifndef pixelstruct_h
#define pixelstruct_h
#include "Arduino.h"

// Create a struct for creating blooms
struct BloomStruct {
  // Define where the center of the bloom is located
  int16_t center = 0;
  // Desired range/breadth of bloom
  double range = 0;
  // Define target color values for the bloom
  double color[3] = {0, 0, 0};
  // Bloom grow state and target
  double cGrow = 0;
  double tGrow = 0;
  // Bloom shrink state and target
  double cShrink = 0;
  double tShrink = 0;
  // Bloom intensity modifier
  double intensity = 0;
  // Keep track of total pixels internally
  uint16_t localPixels = 0;

  // Initialize a new randomized bloom
  void initialize(uint16_t totalPixels) {
    localPixels = totalPixels;
    center = random(0, localPixels);
    range = random(localPixels / 20, localPixels / 10);
    color[1] = random(0,200);
    color[2] = 0;
    color[3] = random(100,255);
    tGrow = random(10,50);
    cGrow = 0;
    tShrink = random(10,50);
    cShrink = tShrink;
  }

  // Grow the bloom one step
  void run() {
    if(cGrow < tGrow) { // Begin growing the bloom to the target
      intensity = cGrow / tGrow;
      cGrow++;
    }
    else if(cShrink > 0) { // Begin shrinking the bloom to 0
      intensity = cShrink / tShrink;
      cShrink--;
    }
    else if(cShrink <= 0) { // If bloom has completed, reinitialize
      initialize(localPixels);
    }
  }

  // Apply the current bloom state to the pixel array
  // PREPARE FOR CRAZY NESTED FOR LOOPS 0_____0
  void apply(uint8_t pixels[][4]) {
    for(uint8_t x=0; x<range; x++) {
      // Calculate the color modifier for the pixel (time*range offset)
      double colorModifier = (intensity * (.9999 - (double(x) / range)));
      // Alternate between positive and negative offset values
      // (Except for when the range is 0 -- when we're in the center)
      for(uint8_t rgb=1; rgb<4; rgb++) {
        // If the color value is 0, set to target color value (no averaging)
        // Also wrapped in if statements to protect from addressing outside
        // the array.
        if((center + x) < localPixels) {
          pixels[center + x][rgb] = ((pixels[center + x][rgb] + (color[rgb] * colorModifier)) / 2);
        }
        if((center - x) > 0) {
          pixels[center - x][rgb] = ((pixels[center - x][rgb] + (color[rgb] * colorModifier)) / 2);
        }
      }
    }
  }
};

#endif
