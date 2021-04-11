// Process a change in the state of the On-Off Switch
//    This turns the brightness to max (if switched on) or to zero (if switched off).
void onOffISR(){
  // If the input is high, set brightness to maximum brightness.
  if(onOffState) brightness = maxBrightness;
  // If the input is low, set brightness to zero.
  else brightness = 0;
}

// Process a high from the Moment-right Switch (ie, moving the momentary switch to the right)
//    This increments the light 'show'/pattern that is currently displaying.
void momentRightISR(){
  // If the patternId is less than the total number of patterns, then increment it;
  //    otherwise, loop back to the beginning by setting patternId to zero.
  if(patternId < numPattern) patternId++;
  else patternId = 0;
}

// Process a high from the Moment-left Switch (ie, moving the momentary switch to the left)
//    This decrements the light 'show'/pattern that is currently displaying.
void momentLeftISR(){
  // If the patternId is greater than zero, then decrement it;
  //    otherwise, loop back to the end by setting patternId to the final pattern number.
  if(patternId > 0) patternId--;
  else patternId = numPattern;
}

// Process a change in the state of the Amplitude Dial
//    This adjusts the brightness relative to the dial location.
void ampDialISR(){
  // Read the analog input from the Amplitude Dial (a value between 0 and 1023).
  ampDialState = analogRead(ampDialPin);
  // Map the received input value to the range of brightnesses and adjust brightness accordingly.
  brightness = map(ampDialState, 0, 1023, 0, maxBrightness);
}
