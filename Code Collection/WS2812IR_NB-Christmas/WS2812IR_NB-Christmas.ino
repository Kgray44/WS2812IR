/*************************************************************
File Name: WS2812IR_NB-Christmas.ino
Processor/Platform: Arduino (D1-mini tested)
Development Environment: Arduino 2.2.1

Download latest code here:
https://github.com/Kgray44/WS2812IR

WS2812IR code meant to be used alongside the tutorial found here:
https://www.hackster.io/k-gray/how-to-use-ir-remote-and-ws2812-leds-with-arduino-342df9

Copyright 2023 K Gray

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Liscense found here:
https://opensource.org/licenses/MIT
 *************************************************************/

#include <WS2812IR_NB.hpp>

int sections = 1;
int currentpixels = 1;
unsigned long lastmillis = 0;
boolean firsts = false;
unsigned long curmillis = 0;
unsigned long lastmil = 0;

constexpr byte IRPin =  2;   // Signal Pin of IR receiver
IRrecv receiver(IRPin);

constexpr byte pixelCount = 120;//250;
constexpr byte PIN = 0;//D3
Adafruit_NeoPixel pixels(pixelCount, PIN, NEO_GRB + NEO_KHZ800);

WS2812IR_NB wsir(&receiver, &pixels, pixelCount);

void setup() {
  wsir.begin();

// warmup the fireflies
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
    wsir.lightning(100,40);
    yield();
  }
  int i=255;
  while (i!=0){
    if (millis() - lastmil >= 10){i--;lastmil = millis();}
    wsir.chaseC(0,i,0,100);
    yield();
  }
  curmillis = curmillis+(lastmil-curmillis-10000);
  wsir.clear();
  while (millis() < curmillis+23000){
    wsir.fireflies(25,1000,5000);
    yield();
  }
  wsir.hue = 0;
  while (millis() < curmillis+26000){
    wsir.strobe(150);
    wsir.lightning(100,40);
    yield();
  }
  unsigned long val = wsir.hue;
  while (millis() < curmillis+28000){
    if (millis() - lastmil >= 1){val = val+12;lastmil=millis();}
    wsir.hue = val;//19115
    wsir.strobe(150);
    wsir.lightning(100,40);
    yield();
  }
  wsir.hue = color(105);
  while (millis() < curmillis+31000){
    wsir.strobe(150);
    wsir.lightning(100,40);
    yield();
  }
  flag = false;
  while (millis() < curmillis+35000){
    flag = !flag;
    if (flag){wsir.hue = color(105);}
    else {wsir.hue = color(0);}
    wsir.chase(100);
    wsir.lightning(100,40);
    yield();
  }
  i=255;
  while (i!=0){
    if (millis() - lastmil >= 10){i--;lastmil = millis();}
    wsir.chaseC(i,0,0,100);
    wsir.lightning(100,40);
    yield();
  }
  curmillis = curmillis+(lastmil-curmillis-35000);
  wsir.clear();
  while (millis() < curmillis+43000){
    wsir.lightning(100,40);
    yield();
  }
  flag = false;
  while (millis() < curmillis+47000){
    flag = !flag;
    if (flag){wsir.hue = color(105);}
    else {wsir.hue = color(0);}
    wsir.chase(100);
    wsir.lightning(100,40);
    yield();
  }
  wsir.clear();
  while (millis() < curmillis+57000){
    wsir.rainbow(5);
    yield();
  }
}

unsigned long color(unsigned long colortoredo){return(map(colortoredo,0,360,0,65536));}
