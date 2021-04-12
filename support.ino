// Set the color of each strip at location j to color r-g-b 
void setAllColor(uint16_t j, float r, float g, float b){
  strip.setPixelColor(STRIP_A(j), r, g, b);
  strip.setPixelColor(STRIP_B(j), r, g, b);
  strip.setPixelColor(STRIP_C(j), r, g, b);
}

// Return the integer address of location i for Strip A.
//    Because this is the first strip, it simply returns the input
//    value (e.g., location 5 on Strip A is the 5th pixel. Keep in
//    mind indexing from 1 vs 0. We go from 0.). 
int STRIP_A(int i){
  return i;
}

// Return the integer address of location i for Strip B.
//    For the second strip, it is in a visually-reversed direction.
//    So, we decrement from the final pin rather than incrementing
//    from the first. E.g. location 5 on Strip B is the 5th pixel
//    from the end of B: 59-5, the 54th pixel.
int STRIP_B(int i){
  return 59-i;
}

// Return the integer address of location i for Strip C.
//    For the third strip, it's in the same direction as the first,
//    so we increment from the beginning of the strip. Thus, 
//    location 5 on Strip C is the 5th pixel from the beginning
//    of C: 60+5, the 65th pixel.
int STRIP_C(int i){
  return 60+i;
}

// Delay for i milliseconds since the last check
//    This delay *can* be interrupted.
void delayMillis(unsigned long int start, unsigned long int i){
  unsigned long int currMillis = 0;
  while((currMillis - start) < i){
    currMillis = millis();
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t wheel(byte wheelPos) {
  if(wheelPos < 85) {
   return strip.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
  } else if(wheelPos < 170) {
   wheelPos -= 85;
   return strip.Color(255 - wheelPos * 3, 0, wheelPos * 3);
  } else {
   wheelPos -= 170;
   return strip.Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
}
