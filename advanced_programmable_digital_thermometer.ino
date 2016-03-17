#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

int backgroundColor[3] = {5,5,5};

void setup() {
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show();
  
}

void loop() {
  int i = 0;
  for (i = -10; i <= 100; i++){
    setDigit(i);
    delay(1000);
  }  
}

void setDigit(signed int temp){
  byte i; //loop counter
  byte j; //loop counter
  byte k; //loop counter
  byte s; //switch case

  byte displayMatrix[8][5];
  const byte digits[11][5][3] = {{{1,1,1},{1,0,1},{1,0,1},{1,0,1},{1,1,1}},
                                 {{1,1,0},{0,1,0},{0,1,0},{0,1,0},{1,1,1}},
                                 {{1,1,1},{0,0,1},{1,1,1},{1,0,0},{1,1,1}},
                                 {{1,1,1},{0,0,1},{0,1,1},{0,0,1},{1,1,1}},
                                 {{1,0,1},{1,0,1},{1,1,1},{0,0,1},{0,0,1}},
                                 {{1,1,1},{1,0,0},{1,1,1},{0,0,1},{1,1,1}},
                                 {{1,1,1},{1,0,0},{1,1,1},{1,0,1},{1,1,1}},
                                 {{1,1,1},{0,0,1},{0,1,0},{0,1,0},{0,1,0}},
                                 {{1,1,1},{1,0,1},{1,1,1},{1,0,1},{1,1,1}},
                                 {{1,1,1},{1,0,1},{1,1,1},{0,0,1},{0,0,1}},
                                 {{0,0,0},{0,0,0},{1,1,1},{0,0,0},{0,0,0}}};
                              
  temp = constrain(temp, -9, 99);

  if (temp  < 0) {s = 1;}
  if (temp == 0) {s = 2;}
  if (temp  > 0) {s = 3;}

  switch ( s ){
    case 1:
      Serial.println("case 1");
      for(i = 0; i < 3; i++){
        for(j = 0; j < 5; j++){
          displayMatrix[i][j] = digits[11][i][j];
          displayMatrix[i+5][j] = digits[abs(temp % 10)][i][j];
        }
      }
      break;
    case 2:
      Serial.println("case 2");
      for(i = 0; i < 5; i++){
        for(j = 0; j < 3; j++){
          displayMatrix[i+5][j] = digits[0][i][j];  
        }
      }
      break;
    case 3:
      Serial.println("case 3");
      for(i = 0; i < 5; i++){
        for(j = 0; j < 3; j++){
          displayMatrix[i][j] = digits[abs(temp / 10 % 10)][i][j];
          displayMatrix[i+5][j] = digits[abs(temp % 10)][i][j];
        }
      }
      break;
  }

  Serial.print("before draw");
  for (i = 0; i < 5; i++){
    for (j = 0; j < 8; j++){
      Serial.print(displayMatrix[j][i]);
      if (displayMatrix[i][j] == 1){
        strip.setPixelColor(i * j, 20, 50, 120);
      }
      else{
        strip.setPixelColor(i * j, 0, 0, 0);
      }
    }
  }
  //strip.setPixelColor(digits[11][i],0,120,20);
  strip.show();
}
