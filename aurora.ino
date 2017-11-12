#include "Adafruit_NeoPixel.h"
#include "pixelstruct.h"
#define PIN 6
#define TOTALPIXELS 450
#define TOTALBLOOMS 10

// Initialize the strip object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(TOTALPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Create an array of pixel structs and blooms
uint8_t pixels[TOTALPIXELS][4] = {0};
BloomStruct blooms[TOTALBLOOMS];

// Initial setup
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

// Begin main loop
void loop() {
  // Initialize all blooms
  for(int8_t x=0; x<TOTALBLOOMS; x++) {
    blooms[x].initialize(TOTALPIXELS);
  }
  // Begin the animation
  aurora();
}

// Function to generate multiple blooms of color
void aurora() {
  while(1) {
  // Iterate through the number of blooms
  for(uint8_t x=0; x<TOTALBLOOMS; x++) {
    // Progress the bloom one step
    blooms[x].run();
    // Apply the bloom to the pixel array
    blooms[x].apply(pixels);
  }
  // Apply our pixel array changes to the strip
  for(uint16_t y=0; y<TOTALPIXELS; y++) {
    strip.setPixelColor(y, pixels[y][1], pixels[y][2], pixels[y][3]);
  }
  // Write all changes to the bus
  strip.show();
  }
}
