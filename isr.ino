void onOffISR(){
  if(onOffState) brightness = maxBrightness;
  else brightness = 0;
}

void momentRightISR(){
  if(patternId < numPattern) patternId++;
  else patternId = 0;
}

void momentLeftISR(){
  if(patternId > 0) patternId--;
  else patternId = numPattern;
}

void ampDialISR(){
  ampDialState = analogRead(ampDialPin);
  brightness = map(ampDialState, 0, 1023, 0, maxBrightness);
}
