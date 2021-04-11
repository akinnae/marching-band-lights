class ColorStrip
{
public:
  uint8_t   effect;
  uint8_t   effects;
  uint16_t  effStep;
  unsigned long effStart;
  ColorStrip(uint8_t toteffects) {
    effect = -1;
    effects = toteffects;
    Reset();
  }
  void Reset(){
    effStep = 0;
    effect = (effect + 1) % effects;
    effStart = millis();
  }
};

struct ColorLoop
{
  uint8_t currentChild;
  uint8_t childs;
  bool timeBased;
  uint16_t cycles;
  uint16_t currentTime;
  ColorLoop(uint8_t totchilds, bool timebased, uint16_t tottime) {currentTime=0;currentChild=0;childs=totchilds;timeBased=timebased;cycles=tottime;}
};

// Sunset colors: light pink, deep red, dark blue
ColorStrip sunsetStrip(30);
struct ColorLoop sunsetLoop(1, false, 1);

// Pastel colors: light purple, light pink, light green, etc.
ColorStrip pastelStrip(30);
struct ColorLoop pastelLoop(1, false, 1);

// Patriotic/USA colors: red, blue, white
ColorStrip usausaStrip(30);
struct ColorLoop usausaLoop(1, false, 1);

// Vandal colors: gold, silver, grey, yellow, black
ColorStrip vandalStrip(30);
struct ColorLoop vandalLoop(1, false, 1);

// Bright rainbow colors: red, orange, yellow, green, blue, purple
ColorStrip rainboStrip(30);
struct ColorLoop rainboLoop(1, false, 1);

// SHARED FUNCTIONS
void setAllColor(uint16_t j, float r, float g, float b){
  strip.setPixelColor(STRIP_A(j), r, g, b);
  strip.setPixelColor(STRIP_B(j), r, g, b);
  strip.setPixelColor(STRIP_C(j), r, g, b);
}

// SUNSET FUNCTIONS
uint8_t sunset_loop() {
  uint8_t ret = 0x00;
  switch(sunsetLoop.currentChild) {
    case 0: 
           ret = sunset_loop_eff();break;
  }
  if(ret & 0x02) {
    ret &= 0xfd;
    if(sunsetLoop.currentChild + 1 >= sunsetLoop.childs) {
      sunsetLoop.currentChild = 0;
      if(++sunsetLoop.currentTime >= sunsetLoop.cycles) {sunsetLoop.currentTime = 0; ret |= 0x02;}
    }
    else {
      sunsetLoop.currentChild++;
    }
  };
  return ret;
}

uint8_t sunset_loop_eff() {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 30
    // Steps: 60 - Delay: 90
    // Colors: 6 (255.184.167, 255.137.194, 158.113.198, 155.30.100, 20.72.131, 54.135.180)
    // Options: rainbowlen=124, toLeft=true, 
  if(millis() - sunsetStrip.effStart < 90 * (sunsetStrip.effStep)) return 0x00;
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<30;j++) {
    ind = sunsetStrip.effStep + j * 0.4838709677419355;
    switch((int)((ind % 60) / 10)) {
      case 0: factor1 = 1.0 - ((float)(ind % 60 - 0 * 10) / 10);
              factor2 = (float)((int)(ind - 0) % 60) / 10;
              setAllColor(j, 255 * factor1 + 255 * factor2, 184 * factor1 + 137 * factor2, 167 * factor1 + 194 * factor2);
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 60 - 1 * 10) / 10);
              factor2 = (float)((int)(ind - 10) % 60) / 10;
              setAllColor(j, 255 * factor1 + 158 * factor2, 137 * factor1 + 113 * factor2, 194 * factor1 + 198 * factor2);
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 60 - 2 * 10) / 10);
              factor2 = (float)((int)(ind - 20) % 60) / 10;
              setAllColor(j, 158 * factor1 + 155 * factor2, 113 * factor1 + 30 * factor2, 198 * factor1 + 100 * factor2);
              break;
      case 3: factor1 = 1.0 - ((float)(ind % 60 - 3 * 10) / 10);
              factor2 = (float)((int)(ind - 30) % 60) / 10;
              setAllColor(j, 155 * factor1 + 20 * factor2, 30 * factor1 + 72 * factor2, 100 * factor1 + 131 * factor2);
              break;
      case 4: factor1 = 1.0 - ((float)(ind % 60 - 4 * 10) / 10);
              factor2 = (float)((int)(ind - 40) % 60) / 10;
              setAllColor(j, 20 * factor1 + 54 * factor2, 72 * factor1 + 135 * factor2, 131 * factor1 + 180 * factor2);
              break;
      case 5: factor1 = 1.0 - ((float)(ind % 60 - 5 * 10) / 10);
              factor2 = (float)((int)(ind - 50) % 60) / 10;
              setAllColor(j, 54 * factor1 + 255 * factor2, 135 * factor1 + 184 * factor2, 180 * factor1 + 167 * factor2);
              break;
    }
  }
  if(sunsetStrip.effStep >= 60) {sunsetStrip.Reset(); return 0x03; }
  else sunsetStrip.effStep++;
  return 0x01;
}

// PASTEL FUNCTIONS
uint8_t pastel_loop() {
  uint8_t ret = 0x00;
  switch(pastelLoop.currentChild) {
    case 0: 
           ret = pastel_loop_eff();break;
  }
  if(ret & 0x02) {
    ret &= 0xfd;
    if(pastelLoop.currentChild + 1 >= pastelLoop.childs) {
      pastelLoop.currentChild = 0;
      if(++pastelLoop.currentTime >= pastelLoop.cycles) {pastelLoop.currentTime = 0; ret |= 0x02;}
    }
    else {
      pastelLoop.currentChild++;
    }
  };
  return ret;
}

uint8_t pastel_loop_eff() {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 30
    // Steps: 60 - Delay: 90
    // Colors: 5 (255.175.171, 164.255.125, 147.218.204, 191.140.223, 255.255.99)
    // Options: rainbowlen=124, toLeft=true, 
  if(millis() - pastelStrip.effStart < 90 * (pastelStrip.effStep)) return 0x00;
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<30;j++) {
    ind = pastelStrip.effStep + j * 0.4838709677419355;
    switch((int)((ind % 60) / 12)) {
      case 0: factor1 = 1.0 - ((float)(ind % 60 - 0 * 12) / 12);
              factor2 = (float)((int)(ind - 0) % 60) / 12;
              setAllColor(j, 255 * factor1 + 164 * factor2, 175 * factor1 + 255 * factor2, 171 * factor1 + 125 * factor2);
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 60 - 1 * 12) / 12);
              factor2 = (float)((int)(ind - 12) % 60) / 12;
              setAllColor(j, 164 * factor1 + 147 * factor2, 255 * factor1 + 218 * factor2, 125 * factor1 + 204 * factor2);
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 60 - 2 * 12) / 12);
              factor2 = (float)((int)(ind - 24) % 60) / 12;
              setAllColor(j, 147 * factor1 + 191 * factor2, 218 * factor1 + 140 * factor2, 204 * factor1 + 223 * factor2);
              break;
      case 3: factor1 = 1.0 - ((float)(ind % 60 - 3 * 12) / 12);
              factor2 = (float)((int)(ind - 36) % 60) / 12;
              setAllColor(j, 191 * factor1 + 255 * factor2, 140 * factor1 + 255 * factor2, 223 * factor1 + 99 * factor2);
              break;
      case 4: factor1 = 1.0 - ((float)(ind % 60 - 4 * 12) / 12);
              factor2 = (float)((int)(ind - 48) % 60) / 12;
              setAllColor(j, 255 * factor1 + 255 * factor2, 255 * factor1 + 175 * factor2, 99 * factor1 + 171 * factor2);
              break;
    }
  }
  if(pastelStrip.effStep >= 60) {pastelStrip.Reset(); return 0x03; }
  else pastelStrip.effStep++;
  return 0x01;
}

// RAINBOW FUNCTIONS
uint8_t rainbo_loop() {
  uint8_t ret = 0x00;
  switch(rainboLoop.currentChild) {
    case 0: 
           ret = rainbo_loop_eff();break;
  }
  if(ret & 0x02) {
    ret &= 0xfd;
    if(rainboLoop.currentChild + 1 >= rainboLoop.childs) {
      rainboLoop.currentChild = 0;
      if(++rainboLoop.currentTime >= rainboLoop.cycles) {rainboLoop.currentTime = 0; ret |= 0x02;}
    }
    else {
      rainboLoop.currentChild++;
    }
  };
  return ret;
}

uint8_t rainbo_loop_eff() {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 30
    // Steps: 60 - Delay: 90
    // Colors: 6 (255.0.0, 255.114.0, 255.255.0, 54.255.79, 36.65.255, 122.16.255)
    // Options: rainbowlen=124, toLeft=true, 
  if(millis() - rainboStrip.effStart < 90 * (rainboStrip.effStep)) return 0x00;
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<30;j++) {
    ind = rainboStrip.effStep + j * 0.4838709677419355;
    switch((int)((ind % 60) / 10)) {
      case 0: factor1 = 1.0 - ((float)(ind % 60 - 0 * 10) / 10);
              factor2 = (float)((int)(ind - 0) % 60) / 10;
              setAllColor(j, 255 * factor1 + 255 * factor2, 0 * factor1 + 114 * factor2, 0 * factor1 + 0 * factor2);
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 60 - 1 * 10) / 10);
              factor2 = (float)((int)(ind - 10) % 60) / 10;
              setAllColor(j, 255 * factor1 + 255 * factor2, 114 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 60 - 2 * 10) / 10);
              factor2 = (float)((int)(ind - 20) % 60) / 10;
              setAllColor(j, 255 * factor1 + 54 * factor2, 255 * factor1 + 255 * factor2, 0 * factor1 + 79 * factor2);
              break;
      case 3: factor1 = 1.0 - ((float)(ind % 60 - 3 * 10) / 10);
              factor2 = (float)((int)(ind - 30) % 60) / 10;
              setAllColor(j, 54 * factor1 + 36 * factor2, 255 * factor1 + 65 * factor2, 79 * factor1 + 255 * factor2);
              break;
      case 4: factor1 = 1.0 - ((float)(ind % 60 - 4 * 10) / 10);
              factor2 = (float)((int)(ind - 40) % 60) / 10;
              setAllColor(j, 36 * factor1 + 122 * factor2, 65 * factor1 + 16 * factor2, 255 * factor1 + 255 * factor2);
              break;
      case 5: factor1 = 1.0 - ((float)(ind % 60 - 5 * 10) / 10);
              factor2 = (float)((int)(ind - 50) % 60) / 10;
              setAllColor(j, 122 * factor1 + 255 * factor2, 16 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
              break;
    }
  }
  if(rainboStrip.effStep >= 60) {rainboStrip.Reset(); return 0x03; }
  else rainboStrip.effStep++;
  return 0x01;
}

// USA FUNCTIONS
uint8_t usausa_loop() {
  uint8_t ret = 0x00;
  switch(usausaLoop.currentChild) {
    case 0: 
           ret = usausa_loop_eff();break;
  }
  if(ret & 0x02) {
    ret &= 0xfd;
    if(usausaLoop.currentChild + 1 >= usausaLoop.childs) {
      usausaLoop.currentChild = 0;
      if(++usausaLoop.currentTime >= usausaLoop.cycles) {usausaLoop.currentTime = 0; ret |= 0x02;}
    }
    else {
      usausaLoop.currentChild++;
    }
  };
  return ret;
}

uint8_t usausa_loop_eff() {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 30
    // Steps: 60 - Delay: 90
    // Colors: 6 (255.0.0, 255.255.255, 255.255.255, 46.47.255, 255.255.255, 255.255.255)
    // Options: rainbowlen=124, toLeft=true, 
  if(millis() - usausaStrip.effStart < 90 * (usausaStrip.effStep)) return 0x00;
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<30;j++) {
    ind = usausaStrip.effStep + j * 0.4838709677419355;
    switch((int)((ind % 60) / 10)) {
      case 0: factor1 = 1.0 - ((float)(ind % 60 - 0 * 10) / 10);
              factor2 = (float)((int)(ind - 0) % 60) / 10;
              setAllColor(j, 255 * factor1 + 255 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 255 * factor2);
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 60 - 1 * 10) / 10);
              factor2 = (float)((int)(ind - 10) % 60) / 10;
              setAllColor(j, 255 * factor1 + 255 * factor2, 255 * factor1 + 255 * factor2, 255 * factor1 + 255 * factor2);
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 60 - 2 * 10) / 10);
              factor2 = (float)((int)(ind - 20) % 60) / 10;
              setAllColor(j, 255 * factor1 + 46 * factor2, 255 * factor1 + 47 * factor2, 255 * factor1 + 255 * factor2);
              break;
      case 3: factor1 = 1.0 - ((float)(ind % 60 - 3 * 10) / 10);
              factor2 = (float)((int)(ind - 30) % 60) / 10;
              setAllColor(j, 46 * factor1 + 255 * factor2, 47 * factor1 + 255 * factor2, 255 * factor1 + 255 * factor2);
              break;
      case 4: factor1 = 1.0 - ((float)(ind % 60 - 4 * 10) / 10);
              factor2 = (float)((int)(ind - 40) % 60) / 10;
              setAllColor(j, 255 * factor1 + 255 * factor2, 255 * factor1 + 255 * factor2, 255 * factor1 + 255 * factor2);
              break;
      case 5: factor1 = 1.0 - ((float)(ind % 60 - 5 * 10) / 10);
              factor2 = (float)((int)(ind - 50) % 60) / 10;
              setAllColor(j, 255 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
              break;
    }
  }
  if(usausaStrip.effStep >= 60) {usausaStrip.Reset(); return 0x03; }
  else usausaStrip.effStep++;
  return 0x01;
}

// VANDAL FUNCTIONS
uint8_t vandal_loop() {
  uint8_t ret = 0x00;
  switch(vandalLoop.currentChild) {
    case 0: 
           ret = vandal_loop_eff();break;
  }
  if(ret & 0x02) {
    ret &= 0xfd;
    if(vandalLoop.currentChild + 1 >= vandalLoop.childs) {
      vandalLoop.currentChild = 0;
      if(++vandalLoop.currentTime >= vandalLoop.cycles) {vandalLoop.currentTime = 0; ret |= 0x02;}
    }
    else {
      vandalLoop.currentChild++;
    }
  };
  return ret;
}

uint8_t vandal_loop_eff() {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 30
    // Steps: 60 - Delay: 90
    // Colors: 6 (70.73.77, 123.146.169, 255.206.0, 215.217.209, 255.255.0, 255.180.0)
    // Options: rainbowlen=124, toLeft=true, 
  if(millis() - vandalStrip.effStart < 90 * (vandalStrip.effStep)) return 0x00;
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<30;j++) {
    ind = vandalStrip.effStep + j * 0.4838709677419355;
    switch((int)((ind % 60) / 10)) {
      case 0: factor1 = 1.0 - ((float)(ind % 60 - 0 * 10) / 10);
              factor2 = (float)((int)(ind - 0) % 60) / 10;
              setAllColor(j, 70 * factor1 + 123 * factor2, 73 * factor1 + 146 * factor2, 77 * factor1 + 169 * factor2);
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 60 - 1 * 10) / 10);
              factor2 = (float)((int)(ind - 10) % 60) / 10;
              setAllColor(j, 123 * factor1 + 255 * factor2, 146 * factor1 + 206 * factor2, 169 * factor1 + 0 * factor2);
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 60 - 2 * 10) / 10);
              factor2 = (float)((int)(ind - 20) % 60) / 10;
              setAllColor(j, 255 * factor1 + 215 * factor2, 206 * factor1 + 217 * factor2, 0 * factor1 + 209 * factor2);
              break;
      case 3: factor1 = 1.0 - ((float)(ind % 60 - 3 * 10) / 10);
              factor2 = (float)((int)(ind - 30) % 60) / 10;
              setAllColor(j, 215 * factor1 + 255 * factor2, 217 * factor1 + 255 * factor2, 209 * factor1 + 0 * factor2);
              break;
      case 4: factor1 = 1.0 - ((float)(ind % 60 - 4 * 10) / 10);
              factor2 = (float)((int)(ind - 40) % 60) / 10;
              setAllColor(j, 255 * factor1 + 255 * factor2, 255 * factor1 + 180 * factor2, 0 * factor1 + 0 * factor2);
              break;
      case 5: factor1 = 1.0 - ((float)(ind % 60 - 5 * 10) / 10);
              factor2 = (float)((int)(ind - 50) % 60) / 10;
              setAllColor(j, 255 * factor1 + 70 * factor2, 180 * factor1 + 73 * factor2, 0 * factor1 + 77 * factor2);
              break;
    }
  }
  if(vandalStrip.effStep >= 60) {vandalStrip.Reset(); return 0x03; }
  else vandalStrip.effStep++;
  return 0x01;
}
