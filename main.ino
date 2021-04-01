#include <Adafruit_NeoPixel.h>
 
#define PIN     6
#define N_LEDS  90
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Set input control
const int onOffPin = 11;          // on/off switch pin
const int momentRightPin = 12;    // momentary toggle right pin
const int momentLeftPin = 13;     // momentary toggle left pin
const int ampDialPin = 9;         // amplitude dial pin (analog)
volatile int onOffState = 0;      // on/off switch status (0=off, 1=on)
volatile int ampDialState = 0;    // amplitude dial status

// Set brightness variables
volatile int brightness = 0;
int maxBrightness = 255;           // sets scale of brightness (max value, ranges from 0 to maxBrightness)

// Set pattern variables
volatile int patternId = 0;       // ID of current pattern
int numPattern = 2;               // total number of patterns

// Set timing details
unsigned long int interval = 60;

// Main function
void setup() {
  strip.begin();

  // Set up pins as interrupt input
  pinMode(onOffPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(onOffPin), onOffISR, CHANGE);
  pinMode(momentRightPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(momentRightPin), momentRightISR, RISING);
  pinMode(momentLeftPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(momentLeftPin), momentLeftISR, RISING);
  pinMode(ampDialPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ampDialPin), ampDialISR, CHANGE);
}

// After initializing in "setup" above, this will loop indefinitely.
void loop() {
  switch(patternId){
    case 0:
      sweep();
      break;
    case 1:
      flash();
      break;
    case 2:
      glowy();
      break;
  }
}

// PATTERN 0: SWEEP
// Sweep colors down all three strips at once in series of four
static void sweep() {
  unsigned long int prevMillis, tempPrevMillis;
  for(uint16_t j=0; j<256; j++){
    prevMillis = millis();
    for(uint16_t i=0; i<34; i++){
      tempPrevMillis = millis();
      // Draw a new pixel on each strip
      strip.setPixelColor(STRIP_A(i)  , wheel((i+j) & brightness)); 
      strip.setPixelColor(STRIP_B(i)  , wheel((i+j) & brightness)); 
      strip.setPixelColor(STRIP_C(i)  , wheel((i+j) & brightness)); 
      // Erase pixel a few steps back on each strip
      strip.setPixelColor(STRIP_A(i)-4, 0);
      strip.setPixelColor(STRIP_B(i)-4, 0);
      strip.setPixelColor(STRIP_C(i)-4, 0); 
      // Display changes
      strip.show();
      // Check if pattern has changed 
      if(patternId!=0) break;
      // Delay (allows for synchronization) 
      delayMillis(tempPrevMillis, interval);
    }
    // Check if pattern has changed 
    if(patternId!=0) break;
    // Delay (allows for synchronization) 
    delayMillis(prevMillis, interval*34);
  }
}

// PATTERN 1: FLASH
// Flash entire strip at once, increasing in pace
static void flash(){
  
}

// PATTERN 2: GLOWY
// Entire strip stays lit and slowly changes color
static void glowy(){
  
}
