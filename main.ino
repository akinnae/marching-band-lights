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
volatile int patternId = 0;       // ID of current pattern (0=sweep, 1=flash, 2=glowy). See functions below.
int numPattern = 2;               // highest ID# of pattern (indexing from zero, so 2 means there are 3 patterns)
int colorSetId = 3;               // ID of current color set. (0=sunset, 1=pastel, 2=patriotic, 3=vandal, 4=rainbow). See color-sets.ino.

// Set timing details
unsigned long int interval = 60;  // scale of timing in milliseconds; higher = slower patterns

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
    // Pattern 0: Sweep
    case 0:
      sweep();
      break;
    // Pattern 1: Flash
    case 1:
      flash();
      break;
    // Pattern 2: Glowy
    case 2:
      glowy();
      break;
  }
}

// PATTERN 0: SWEEP
// Sweep colors down all three strips at once in series of four
static void sweep() {
  
  // VARIABLES
  // Create storage for time markers (allows for synchronization)
  unsigned long int tempPrevMillis;
  // Choose length of the series that sweeps down the strip
  int lenSeries = 4;

  // LOOP
  for(uint16_t i=0; i<(30+lenSeries); i++){
    tempPrevMillis = millis();
    if(selectColorSet(colorSetId) & 0x01){
      // Erase all pixels before the lit series
      for(int j=0; j<i; j++)
        setAllColor(j-lenSeries, 0, 0, 0);
      // Erase all pixels after the lit series
      for(int j=i; j<30; j++)
        setAllColor(j+1, 0, 0, 0);
      // Display changes
      strip.show();
      // Check if pattern has changed; if so, exit
      if(patternId!=0) break;
      // Delay (allows for synchronization) 
      delayMillis(tempPrevMillis, interval);
    }
  }
}

// PATTERN 1: FLASH
// Flash entire strip at once, increasing in pace
static void flash(){
  
  // VARIABLES
  // lenCycle is the number of on/off flash pairs
  int lenCycle = 50;
  // startMillis is the length of time in milliseconds that each
  //    on OR off mode will take at the beginning of this pattern
  int startMillis = interval * 10;
  // finalMillis is the length of time in milliseconds that each
  //    on OR off mode will take at the end of the pattern.
  //    If finalMillis>startMillis, this pattern will get slower
  //    rather than faster. If they are equal, the pattern will
  //    simply blink at a consistent rate.
  int finalMillis = interval;
  // tempMillis will store the length of time each on OR off mode
  //    takes at any given point. 
  int tempMillis;

  // LOOP
  for(int i=0; i<lenCycle; i++){
    // Set tempMillis by mapping i to the range of startMillis to 
    //    finalMillis.
    tempMillis = map(i, 0, lenCycle, startMillis, finalMillis);
    
    // Turn strip on
    selectColorSet(colorSetId);
    strip.show();
    // Check if pattern has changed; exit if so
    if(patternId != 1) break;
    // Keep strip on for tempMillis milliseconds
    delayMillis(millis(), tempMillis);
  
    // Turn strip off
    strip.clear();
    strip.show();
    // Check if pattern has changed; exit if so
    if(patternId != 1) break;
    // Keep strip off for tempMillis milliseconds
    delayMillis(millis(), tempMillis);
  }
}

// PATTERN 2: GLOWY
// Entire strip stays lit and slowly changes color
//    Support functions are found in color-sets.ino.
static void glowy(){
  if(selectColorSet(colorSetId) & 0x01)
    // Display changes
    strip.show();
}
