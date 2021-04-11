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
