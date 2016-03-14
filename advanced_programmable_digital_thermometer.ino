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

void setDigit(signed int tempDigit){
 int i = 0;
 int j = 0;
 
 signed int static firstDigit = 0;
 signed static secondDigit = 0;
 
 signed int static firstDigitPrevious = 0;
 signed int static secondDigitPrevious = 0;
 
 const int digits[11][13] = {{0,1,2,10,18,26,34,33,32,24,16,8,NULL},
                             {0,1,9,17,25,32,33,34,NULL,NULL,NULL,NULL,NULL},
                             {0,1,2,10,18,17,16,24,32,33,34,NULL,NULL},
                             {0,1,2,10,18,26,34,33,32,17,NULL,NULL,NULL},
                             {0,8,16,17,2,10,18,26,34,NULL,NULL,NULL,NULL},
                             {2,1,0,8,16,17,18,26,34,33,32,NULL,NULL},
                             {2,1,0,8,16,24,32,33,34,26,18,17,NULL},
                             {0,1,2,10,17,25,33,NULL,NULL,NULL,NULL,NULL,NULL},
                             {0,1,2,10,18,17,16,24,32,33,34,26,8},
                             {17,16,8,0,1,2,10,18,26,34,NULL,NULL,NULL},
                             {NULL,16,17,18,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}};//negativ
  
  tempDigit = constrain(tempDigit, -9, 99);
  
  firstDigit = abs(tempDigit / 10 % 10);
  secondDigit = abs(tempDigit % 10);
  
  if ((firstDigitPrevious != firstDigit) or (secondDigitPrevious != secondDigit))
  {
    firstDigitPrevious = firstDigit;
    secondDigitPrevious = secondDigit;
    
    setBackroundColor(backgroundColor);
    for (i = 0; i<13;i++)
    { 
      if (tempDigit > 9){ // skip first digit if less then 10
      strip.setPixelColor(digits[firstDigit][i],0,120,20);
    }
    else if ((tempDigit < 0) && (digits[10][i] != NULL)) { //if negative numbers
      strip.setPixelColor(digits[10][i],0,120,20);
    }
    
    strip.setPixelColor(digits[secondDigit][i]+4,0,120,20);
    
    strip.show();
    }
  }
}


void setBackroundColor(int* rgb)
{
  int i = 0;
  for (i = 0; i<40; i++)
  {
    strip.setPixelColor(i,rgb[0],rgb[1],rgb[2]);
  }
  strip.show();  
}
