#include <Adafruit_NeoPixel.h>
 
#define PIN     6
#define N_LEDS  90
#define STRIP1  0
#define STRIP2  30
#define STRIP3  60
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Set input control
const int buttonPin = 11;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

// Main function
void setup() {
  strip.begin();
  pinMode(buttonPin, INPUT);
}

// After initializing in "setup" above, this will loop indefinitely.
void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // Check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
      // change LED color to green:
      chase(strip.Color(0, 255, 0)); // Green
  // If the button is not pressed...
  } else {
      // change LED color to blue:
      chase(strip.Color(0, 0, 255)); // Blue
  }
}

// Chase colors down all three strips at once in light series of four
static void chase(uint32_t c) {
  for(uint16_t i=0; i<30+4; i++) {
      // Draw a new pixel on each strip
      strip.setPixelColor(STRIP1+i  , c); 
      strip.setPixelColor(STRIP2+i  , c); 
      strip.setPixelColor(STRIP3+i  , c); 
      // Erase pixel a few steps back on each strip
      strip.setPixelColor((STRIP1+i)-4, 0);
      strip.setPixelColor((STRIP2+i)-4, 0);
      strip.setPixelColor((STRIP3+i)-4, 0); 
      // Display changes
      strip.show();
      // Sets speed of chase
      delay(60);
  }
}
