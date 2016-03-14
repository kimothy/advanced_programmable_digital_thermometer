#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

int backgroundColor[3] = {5,5,5};

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
}

void loop() {
  // put your main code here, to run repeatedly:
  setDigit(21);
  delay(1000);
  setDigit(21);
  delay(1000);
  setDigit(22);
  delay(1000);
}

void setDigit(signed int temp){
 unsigned int i = 0;
 unsigned int j = 0;
 
 const int digits[11][13] = {{0,1,2,10,18,26,34,33,32,24,16,8,-1},
                             {0,1,9,17,25,32,33,34,-1,-1,-1,-1,-1},
                             {0,1,2,10,18,17,16,24,32,33,34,-1,-1},
                             {0,1,2,10,18,26,34,33,32,17,-1,-1,-1},
                             {0,8,16,17,2,10,18,26,34,-1,-1,-1,-1},
                             {2,1,0,8,16,17,18,26,34,33,32,-1,-1},
                             {2,1,0,8,16,24,32,33,34,26,18,17,-1},
                             {0,1,2,10,17,25,33,-1,-1,-1,-1,-1,-1},
                             {0,1,2,10,18,17,16,24,32,33,34,26,8},
                             {17,16,8,0,1,2,10,18,26,34,-1,-1,-1},
                             {-1,16,17,18,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
  
  unsigned int displayMatrixNext[40];
  unsigned int tempDigit[2];

  temp = constrain(temp, -9, 99);
  tempDigit[0] = abs(temp / 10 % 10);
  tempDigit[1] = abs(temp % 10);
  
  for (i = 0; i < 40; i++){
    for (j = 0; i < 13; j++){
      if (i == digits[tempDigit[0]][j]){
        displayMatrixNext[i] = 1;
      } 
      if (i == digits[tempDigit[1]][j]){
        displayMatrixNext[i+5] = 1;
      }
    }
  }

  for (i = 0; i < 40; i++){
    if (displayMatrixNext[i] == 1){
            strip.setPixelColor(displayMatrixNext[i],0,120,20);
    }
  }
  strip.show();
}
