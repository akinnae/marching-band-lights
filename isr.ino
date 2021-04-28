// Process a high from the interrupt input (isrPin = 10), which suggests something in the
//    control array changed (arrPin = 9).
void mainISR(){
  // Handle brightness input
  // Read the analog input from the array (a value between 0 and 255).
  ampDialState = arrayIn[arrBrightness];
  // Map the received input value to the range of brightnesses and adjust brightness accordingly.
  brightness = map(ampDialState, 0, 255, 0, maxBrightness);

  // Handle left/right show input
  //    This increments/decrements the light 'show'/pattern that is currently displaying. 
  //    Right = increment   Left = decrement
  if(arrayIn[arrRightShow]){
      // If the patternId is less than the total number of patterns, then increment it;
      //    otherwise, loop back to the beginning by setting patternId to zero.
      if(patternId < numPattern) patternId++;
      else patternId = 0;
  }
  if(arrayIn[arrLeftShow]){
    // If the patternId is greater than zero, then decrement it;
    //    otherwise, loop back to the end by setting patternId to the final pattern number.
    if(patternId > 0) patternId--;
    else patternId = numPattern;
  }

  // Handle on/off input
  // If the input is 1, set brightness to maximum brightness.
  if(arrayIn[arrOnOff]) brightness = maxBrightness;
  // If the input is low, set brightness to zero.
  else brightness = 0;
}
