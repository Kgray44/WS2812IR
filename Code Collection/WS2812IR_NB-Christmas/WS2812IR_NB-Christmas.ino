#include <WS2812IR_NB.hpp>

int sections = 1;
int currentpixels = 1;
unsigned long lastmillis = 0;
boolean firsts = false;
unsigned long curmillis = 0;

constexpr byte IRPin =  2;   // Signal Pin of IR receiver
IRrecv receiver(IRPin);

constexpr byte pixelCount = 120;//250;
constexpr byte PIN = 0;
Adafruit_NeoPixel pixels(pixelCount, PIN, NEO_GRB + NEO_KHZ800);

constexpr byte stripPin = 0; //D3
WS2812IR_NB wsir(&receiver, &pixels, pixelCount);

void setup() {
  pixels.begin();
  Serial.begin(115200);
  wsir.begin();

  curmillis = millis();
  while (millis() < curmillis+10000){
    wsir.fireflies(25,1000,5000);
    yield();
  }
}

void loop(){
  curmillis = millis();
  wsir.hue = 0;
  while (millis() < curmillis+2000){
    wsir.chase(100);
    yield();
  }
  wsir.hue = color(105);
  while (millis() < curmillis+4000){
    wsir.chase(100);
    yield();
  }
  bool flag = false;
  while (millis() < curmillis+10000){
    flag = !flag;
    if (flag){wsir.hue = color(105);}
    else {wsir.hue = color(0);}
    wsir.chase(100);
    yield();
  }
  wsir.clear();
  while (millis() < curmillis+20000){
    wsir.fireflies(25,1000,5000);
    yield();
  }
  wsir.hue = 0;
  while (millis() < curmillis+23000){
    wsir.strobe(150);
    yield();
  }
  unsigned long val = wsir.hue;
  unsigned long lastmil = 0;
  while (millis() < curmillis+25000){
    if (millis() - lastmil >= 1){val = val+12;lastmil=millis();}
    wsir.hue = val;//19115
    wsir.strobe(150);
    yield();
  }
  wsir.hue = color(105);
  while (millis() < curmillis+28000){
    wsir.strobe(150);
    yield();
  }
  flag = false;
  while (millis() < curmillis+32000){
    flag = !flag;
    if (flag){wsir.hue = color(105);}
    else {wsir.hue = color(0);}
    wsir.chase(100);
    yield();
  }
  wsir.clear();
  while (millis() < curmillis+40000){
    wsir.lightning(100,40);
    yield();
  }
  flag = false;
  while (millis() < curmillis+44000){
    flag = !flag;
    if (flag){wsir.hue = color(105);}
    else {wsir.hue = color(0);}
    wsir.chase(100);
    yield();
  }
}

unsigned long color(unsigned long colortoredo){return(map(colortoredo,0,360,0,65536));}
