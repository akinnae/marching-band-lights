#include <Adafruit_NeoPixel.h>

// Set up the output/LED information
#define PIN     6                 // output pin
#define N_LEDS  90                // total number of pixels in the strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Set control input pin IDs and their states
const int onOffPin = 11;          // on/off switch pin
const int momentRightPin = 12;    // momentary toggle right pin
const int momentLeftPin = 13;     // momentary toggle left pin
const int ampDialPin = 9;         // amplitude dial pin (analog)
volatile int onOffState = 0;      // on/off switch status (0=off, 1=on)
volatile int ampDialState = 0;    // amplitude dial status

// Set brightness variables
volatile int brightness = 0;       // the current brightness (begins at zero)
int maxBrightness = 255;           // sets scale of brightness (max value, ranges from 0 to maxBrightness)

// Set pattern variables
volatile int patternId = 0;       // ID of current pattern
int numPattern = 2;               // total number of patterns

// Set timing details
unsigned long int interval = 60;

// Main function
void setup() {
  strip.begin();

  // SET UP PINS AS INTERRUPT INPUT
  // On-Off Switch interrupts upon a *change* (up or down) in input signal.
  //    This turns the brightness to max (if switched on) or to zero (if switched off).
  //    The onOffPin (pin number defined above) reads this input, 
  //    and onOffISR is the function that processes the input and changes behaviour.
  pinMode(onOffPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(onOffPin), onOffISR, CHANGE);
  // Moment-right Switch (ie, moving the momentary switch to the right) increments the 
  //    light 'show'/pattern that's displaying. The input defaults to low, and 
  //    interrupts only on rising (0->1). patternId is incremented.
  //    The momentRightPin (pin number defined above) reads this input, 
  //    and momentRightISR is the function that processes the input and changes behaviour.
  pinMode(momentRightPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(momentRightPin), momentRightISR, RISING);
  // Moment-left Switch (ie, moving the momentary switch to the left) decrements the 
  //    light 'show'/pattern that's displaying. The input defaults to low, and 
  //    interrupts only on rising (0->1). patternId is decremented.
  //    The momentLeftPin (pin number defined above) reads this input, 
  //    and momentLeftISR is the function that processes the input and changes behaviour.  
  pinMode(momentLeftPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(momentLeftPin), momentLeftISR, RISING);
  // Amplitude Dial interrupts upon a *change* (up or down) in input signal.
  //    This adjusts the brightness in proportion to the change in dial position.
  //    The ampDialPin (pin number defined above) reads this input, 
  //    and ampDialISR is the function that processes the input and changes behaviour.
  pinMode(ampDialPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ampDialPin), ampDialISR, CHANGE);
}

// After initializing in "setup" above, this will loop indefinitely.
void loop() {
  // Depending on which pattern is currently selected (via patternId), 
  //    do one cycle of that pattern.
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
      // Check if pattern has changed; if so, exit
      if(patternId!=0) break;
      // Delay (allows for synchronization) 
      delayMillis(tempPrevMillis, interval);
    }
    // Check if pattern has changed; if so, exit
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
