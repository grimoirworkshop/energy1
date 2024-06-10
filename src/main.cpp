#include <Arduino.h>

#include <FastLED.h>
bool elmo = false;
bool jokeOfTheDay = false;
bool telephoneJoke = false;
bool facePuzzle = false;

class strip{
  public:
    uint16_t numberOfLeds;
    uint16_t startingLED;
    uint8_t mode = 0; //0 is off, 1 is fill pipe, 2 is chase pipe, 3 is fill out, 4 is chase out
    uint16_t step =0;
    
    strip(uint16_t x, uint16_t y){
      numberOfLeds = x;
      startingLED = y;
    }
};

uint8_t chargeLevel = 0;
void fillColor(uint16_t, uint8_t);

strip strip1(200, 0);
strip stripOut(340, strip1.numberOfLeds);

unsigned long elmoTimer;
const uint16_t elmoOffTimer = 15000; 
const uint16_t prankDelay = 3000; 

CRGB leds[540];
int frameDuration = 10;
unsigned long timer;
void assignLEDs(strip&);
void elmoLaughs();
void turnOnLight(uint8_t);

void setup() {
    elmoTimer = 0;
  pinMode(A0, INPUT_PULLUP);  //Elmo
  pinMode(A1, INPUT_PULLUP);  //joke
  pinMode(A2, INPUT_PULLUP);  //prank
  pinMode(A3, INPUT_PULLUP);  //faces
    
  pinMode(A4, OUTPUT);    // video pranks
  digitalWrite(A4, HIGH);
  
  pinMode(8, OUTPUT);  //elmolights
  digitalWrite(8, LOW);
  delay(200);
 pinMode(2, OUTPUT);  //red
 digitalWrite(2, LOW);
 delay(200);
 pinMode(3, OUTPUT);  //yellow
 digitalWrite(3, LOW);
 delay(200);
 pinMode(4, OUTPUT);  //green
 digitalWrite(4, LOW);
 delay(200);
 pinMode(5, OUTPUT);  //blue
 digitalWrite(5, LOW);
 delay(200);
 pinMode(6, OUTPUT);  //elmo DOLL
 digitalWrite(6, LOW);
 delay(200);
 pinMode(7, OUTPUT);  //door2
 digitalWrite(7, HIGH);
 delay(200);
 pinMode(10, OUTPUT); //door2 light
 digitalWrite(10, HIGH);
 digitalWrite(8, LOW);
 
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(8, LOW);
  digitalWrite(A6, HIGH);
  FastLED.addLeds<NEOPIXEL, 11>(leds, 0, strip1.numberOfLeds);
  FastLED.addLeds<NEOPIXEL, 12>(leds, strip1.numberOfLeds, stripOut.numberOfLeds);
  
  
  FastLED.setBrightness(50);

  timer = millis();
  for (uint16_t i =0; i<stripOut.startingLED + stripOut.numberOfLeds; i++){
    leds[i]= CRGB::White;
    delay(2);FastLED.show();
    for (uint16_t j =0; j<stripOut.startingLED + stripOut.numberOfLeds; j++){
        leds[j].fadeToBlackBy(10);
    }
  }
  for (int i = 0; i<20; i++){
    for (uint16_t j =0; j<stripOut.startingLED + stripOut.numberOfLeds; j++){
        leds[j].fadeToBlackBy(10);
    }

  }
  
  
  FastLED.setBrightness(150);
  frameDuration = 50;
  }

void loop() {
  
  if ((digitalRead(A0) == LOW) and (elmo == false)) {
    strip1.mode = 1;
    strip1.step = 0;
    elmo = true;
    chargeLevel++;
    digitalWrite(6, LOW);
    digitalWrite(8, LOW);
    elmoTimer = millis();
      }
  if ((digitalRead(A1) == LOW) and (jokeOfTheDay == false)) {
    strip1.mode = 1;
    strip1.step = 0;
    jokeOfTheDay = true;
    chargeLevel++;
    digitalWrite(6, LOW);
    digitalWrite(8, LOW);
    elmoTimer = millis();
  }
  if ((digitalRead(A2) == LOW) and (telephoneJoke == false)) {
    strip1.mode = 1;
    strip1.step = 0;
    telephoneJoke = true;
    digitalWrite(A4, LOW);
    chargeLevel++;
    delay(prankDelay);  
    digitalWrite(6, LOW);
    digitalWrite(8, LOW);
    elmoTimer = millis();
    digitalWrite(A4, HIGH);
      }
  if ((digitalRead(A3) == LOW) and (facePuzzle == false)) {
    strip1.mode = 1;
    strip1.step = 0;
    facePuzzle = true;
    chargeLevel++;
        digitalWrite(6, LOW);
    digitalWrite(8, LOW);
    elmoTimer = millis();
  }
  
  if ((millis()-timer) > frameDuration){
    assignLEDs(strip1);
    assignLEDs(stripOut);
    timer = millis();
  }
  FastLED.show();
  elmoLaughs();
}
void assignLEDs(strip& led){
  switch (led.mode)  {    
    case 0:
      fillColor(led.step + led.startingLED, 0);
      led.step++;
      if (led.step == led.numberOfLeds){
        
        led.step = 0;
      }
      break;
    case 1:
      fillColor(led.step + led.startingLED, chargeLevel);
      led.step++;
      if (led.step == led.numberOfLeds){
        turnOnLight(chargeLevel);
        led.mode--;
        led.step = 0;
        //digitalWrite(6, HIGH);
      }     
      break;
    case 2:
      break;
    case 3:
      fillColor(led.step + led.startingLED, 1);
      led.step++;
      if (led.step == 163){
        digitalWrite(7, LOW);
        digitalWrite(10, HIGH);
      }
      if (led.step == led.numberOfLeds){
        led.mode++;
        led.step = 0;
        frameDuration = 50;
      }     
      break;
    case 4:
      for (uint8_t i =0; i<34; i++){
         leds[(i*10 )+ led.step+stripOut.startingLED] = CRGB::Red;
      }
      
      led.step++;
      if (led.step == 10){
        
        led.step = 0;
      }   
      for (uint16_t j =stripOut.startingLED; j<stripOut.startingLED + stripOut.numberOfLeds; j++){
        leds[j].fadeToBlackBy(25);
      }  
      break;
    default:
      break;
  }
}
void fillColor(uint16_t Led, uint8_t ChargeLevel){
  switch (ChargeLevel)
  {
  case 0:
    leds[Led] = CRGB::Black;
    break;
  case 1:
    leds[Led] = CRGB::Red;
    break;
  case 2:
    leds[Led] = CRGB::Yellow;
    break;
  case 3:
    leds[Led] = CRGB::Green;
    break;
  case 4:
    leds[Led] = CRGB::Blue;
    break;
  default:
    break;
  }
}
void turnOnLight(uint8_t level){
  switch (level)
  {
  case 0:
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);   
    break;
  case 1:
   digitalWrite(2, LOW);
   break;
  case 2:
   digitalWrite(3, LOW);
   break;
  case 3:
   digitalWrite(4, LOW);
   break;
  case 4:
   digitalWrite(5, LOW);
   if (stripOut.mode ==0) {
    stripOut.mode = 3;
    stripOut.step = 0;
   }
   break;
  default:
    break;
  }
}
void elmoLaughs(){
  if (millis()>(elmoTimer+elmoOffTimer)) {
    digitalWrite(8, HIGH);
    digitalWrite(6, HIGH);
  }
  
}