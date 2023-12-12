/*************************************************************
File Name: WS2812IR_NB.hpp
Processor/Platform: Arduino (Nano tested)
Development Environment: Arduino 2.0.13

Download latest code here:
https://github.com/Kgray44/WS2812IR

Driveway Gates code meant to be used alongside the tutorial found here:
https://www.hackster.io/k-gray/how-to-use-ir-remote-and-ws2812-leds-with-arduino-342df9

Copyright 2022 K Gray

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

#ifndef WS2812IR_NB_h
#define WS2812IR_NB_h

#include "Arduino.h"
#include <IRremote.hpp>
#include <Adafruit_NeoPixel.h>

#define testIR false

int bright = 127;
int modecount = 0;
bool mode = false;
bool on = true;
bool update = true;

int currentpixel=0;
int firstpixelhue=0;
bool flash=false;
int t=0;
int d=0;
int p=0;
bool first=false;
int section=1;
int pc=0;

struct structu {
  int value=0;
  unsigned long lastm=0;
  int timeb=0;
  int number=0;
  bool rising=true;
  bool popping=false;
};
structu pixelF[30];

class WS2812IR_NB
{
  public:
    IRrecv* receiver;
    Adafruit_NeoPixel *pixels;
    size_t pixelsCount;

    unsigned long hue=0;

    unsigned long lastmillis=0;
    unsigned long lastmilliss=0;

    int modeAmount = 6;
    int hueinc = 1000;
    int brightinc = 20;


    WS2812IR_NB(IRrecv* r, Adafruit_NeoPixel *p, size_t n) : receiver(r), pixels(p), pixelsCount(n) {}

    void begin(bool irblink13=true, int baudrate=9600) {
      receiver->enableIRIn(); // Start the receiver
      receiver->blink13(irblink13);
      pixels->begin();
      Serial.begin(baudrate);
      clear();
    }

    void listenIR() {
      if (receiver->decode()) {
        handleKey();
        receiver->resume();  // Receive the next value
      }
    }

    void clear(){
      pixels->fill(pixels->Color(0,0,0),0,pixelsCount);
      pixels->show();
    }
    
    void strip(int R, int G, int B){
      pixels->fill(pixels->Color(R, G, B),0,pixelsCount);
      pixels->show();
    }

    void striphue(int hue){
      pixels->fill(pixels->gamma32(pixels->ColorHSV(hue)),0,pixelsCount);
      pixels->show();
    }

    void rainbow(int speed){
      if (millis() - lastmillis > 5){
        currentpixel++;
        int pixelHue = firstpixelhue + (currentpixel * 65536L / pixelsCount);
        pixels->setPixelColor(currentpixel,pixels->ColorHSV(pixelHue));
        if (currentpixel >= pixelsCount){
          pixels->show();
          currentpixel=0;
          firstpixelhue=firstpixelhue+400;//256
          lastmillis = millis();
        }
      }
    }
    
    void lightning(int ledoffdelay=500,int ledondelay=50){//recommended lower delays for a longer strip
      if (millis() - lastmilliss > t && !flash){
        pixels->setPixelColor(p,pixels->Color(255,255,255));
        pixels->show();
        flash = true;
        lastmilliss = millis();
      }
      else if (millis() - lastmilliss > d && flash){
        pixels->setPixelColor(p,pixels->Color(0,0,0));
        pixels->show();
        flash = false;
        lastmilliss = millis();
        t = random(10,ledoffdelay);
        d = random(4,ledondelay);
        p = random(0,pixelsCount);
      }
    }

    void strobe(int speed){
      if (millis() - lastmillis > speed){
        if (first){
          currentpixel=currentpixel+6;
          pixels->fill(pixels->gamma32(pixels->ColorHSV(hue)),currentpixel,currentpixel+3);
          pixels->fill(pixels->Color(0,0,0),currentpixel+3,currentpixel+6);
          if (currentpixel >= pixelsCount){
            pixels->show();
            currentpixel=0;
            first = false;
            lastmillis = millis();
          }
        }
        else {
          currentpixel=currentpixel+6;
          pixels->fill(pixels->Color(0,0,0),currentpixel,currentpixel+3);
          pixels->fill(pixels->gamma32(pixels->ColorHSV(hue)),currentpixel+3,currentpixel+6);
          if (currentpixel >= pixelsCount){
            pixels->show();
            currentpixel=0;
            first = true;
            lastmillis = millis();
          }
        }
      }
    }

    void chase(int speed){
      if (millis() - lastmillis > speed){
        if (section == 1){
          currentpixel=currentpixel+3;
          pixels->setPixelColor(currentpixel,pixels->gamma32(pixels->ColorHSV(hue)));
          pixels->setPixelColor(currentpixel-1,pixels->Color(0,0,0));
          if (currentpixel >= pixelsCount){
            pixels->show();
            currentpixel=1;
            section = 2;
            lastmillis = millis();
          }
        }
        else if (section == 2){
          currentpixel=currentpixel+3;
          pixels->setPixelColor(currentpixel,pixels->gamma32(pixels->ColorHSV(hue)));
          pixels->setPixelColor(currentpixel-1,pixels->Color(0,0,0));
          if (currentpixel >= pixelsCount){
            pixels->show();
            currentpixel=2;
            section = 3;
            lastmillis = millis();
          }
        }
        else {
          currentpixel=currentpixel+3;
          pixels->setPixelColor(currentpixel,pixels->gamma32(pixels->ColorHSV(hue)));
          pixels->setPixelColor(currentpixel-1,pixels->Color(0,0,0));
          if (currentpixel >= pixelsCount){
            pixels->show();
            currentpixel=0;
            section = 1;
            lastmillis = millis();
          }
        }
      }
    }

    void chaseC(int R, int G, int B, int speed){
      if (millis() - lastmillis > speed){
        if (section == 1){
          currentpixel=currentpixel+3;
          pixels->setPixelColor(currentpixel,pixels->Color(R,G,B));
          pixels->setPixelColor(currentpixel-1,pixels->Color(0,0,0));
          if (currentpixel >= pixelsCount){
            pixels->show();
            currentpixel=1;
            section = 2;
            lastmillis = millis();
          }
        }
        else if (section == 2){
          currentpixel=currentpixel+3;
          pixels->setPixelColor(currentpixel,pixels->Color(R,G,B));
          pixels->setPixelColor(currentpixel-1,pixels->Color(0,0,0));
          if (currentpixel >= pixelsCount){
            pixels->show();
            currentpixel=2;
            section = 3;
            lastmillis = millis();
          }
        }
        else {
          currentpixel=currentpixel+3;
          pixels->setPixelColor(currentpixel,pixels->Color(R,G,B));
          pixels->setPixelColor(currentpixel-1,pixels->Color(0,0,0));
          if (currentpixel >= pixelsCount){
            pixels->show();
            currentpixel=0;
            section = 1;
            lastmillis = millis();
          }
        }
      }
    }

    void fireflies(int amount=15, int timeon=1000, int timeoff=12000){
      pc++; if (pc>amount){pc=0;}
      if (millis() - pixelF[pc].lastm > pixelF[pc].timeb){
        if (pixelF[pc].rising==true){
          pixelF[pc].value=pixelF[pc].value+10;
          pixels->setPixelColor(pixelF[pc].number, pixels->Color(pixelF[pc].value,pixelF[pc].value,map(pixelF[pc].value,0,255,0,80)));
          pixels->show();
          if (pixelF[pc].value >= 250){
            pixelF[pc].value=250;
            pixels->setPixelColor(pixelF[pc].number, pixels->Color(pixelF[pc].value,pixelF[pc].value,map(pixelF[pc].value,0,255,0,80)));
            pixels->show();
            pixelF[pc].timeb=random(50,timeon);
            pixelF[pc].lastm=millis();
            pixelF[pc].rising=false;
          }
        }
        else {
          pixelF[pc].value=pixelF[pc].value-10;
          pixels->setPixelColor(pixelF[pc].number, pixels->Color(pixelF[pc].value,pixelF[pc].value,map(pixelF[pc].value,0,255,0,80)));
          pixels->show();
          if (pixelF[pc].value <= 0){
            pixelF[pc].value=0;
            pixels->setPixelColor(pixelF[pc].number, pixels->Color(0,0,0));
            pixels->show();
            pixelF[pc].timeb=random(1000,timeoff);
            pixelF[pc].lastm=millis();
            pixelF[pc].rising=true;
            pixelF[pc].number=random(0,pixelsCount);
            //reduces flickering due to overlapping previous firefly pixels that are still running
	          for (int t=0;t<=amount;t++){
	            if (pixelF[t].number == pixelF[pc].number){
	              pc++;//pixelF[pc].number=pixelF[pc].number+1;
              }
            }
          }
        }
      }
    }

    void popcorn(int amount=15, int timeon=1800, int timeoff=10000){
      pc++; if (pc>amount){pc=0;}
      if (millis() - pixelF[pc].lastm > pixelF[pc].timeb){
        if (pixelF[pc].rising==true){
          pixelF[pc].value=pixelF[pc].value+5;
          pixels->setPixelColor(pixelF[pc].number, pixels->Color(pixelF[pc].value,0,0));
          pixels->show();
          if (pixelF[pc].value >= 255){
            pixelF[pc].value=255;
            pixels->setPixelColor(pixelF[pc].number, pixels->Color(pixelF[pc].value,0,0));
            pixels->show();
            pixelF[pc].timeb=random(100,timeon);
            pixelF[pc].lastm=millis();
            pixelF[pc].rising=false;
            pixelF[pc].popping=true;
          }
        }
        else if (pixelF[pc].popping==true){
          pixels->setPixelColor(pixelF[pc].number, pixels->Color(255,255,255));
          pixels->show();
          pixelF[pc].rising=false;
          pixelF[pc].number=random(0,pixelsCount);
          pixelF[pc].popping=false;
        }
        else {
          pixelF[pc].value=pixelF[pc].value-10;
          pixels->setPixelColor(pixelF[pc].number, pixels->Color(pixelF[pc].value,pixelF[pc].value,pixelF[pc].value));
          pixels->show();
          if (pixelF[pc].value <= 0){
            pixelF[pc].value=0;
            pixels->setPixelColor(pixelF[pc].number, pixels->Color(0,0,0));
            pixels->show();
            pixelF[pc].timeb=random(1000,timeoff);
            pixelF[pc].lastm=millis();
            pixelF[pc].rising=true;
            pixelF[pc].number=random(0,pixelsCount);
          }
        }
      }
    }

    void takeStep(){
      if (on){
        pixels->setBrightness(bright);
        if (!mode){
          if (update){
            striphue(hue);
            update=false;
          }
        }
        else {
          if (modecount == 0){
            strobe(100);
          }
          else if (modecount == 1){
            chase(20);
          }
          else if (modecount == 2){
            lightning(350,50);
          }
          else if (modecount == 3){
            rainbow(0);
          }
          else if (modecount == 4){
            fireflies(20,1000,12000);
          }
          else if (modecount == 5){
            popcorn(15,1800,10000);
          }
        }
      }
      else {
        if (update){
          clear();
          update=false;
        }
      }
    }


  private:
    
    void handleKey() {
      uint16_t command;
      if (receiver->decodedIRData.protocol == 7 && !testIR){
        command = receiver->decodedIRData.command;
      }
      if (testIR){
        Serial.println(command);
        return;
      }
      Serial.println("Protocol:" + String(receiver->decodedIRData.protocol));

      switch (command) {
        case 0:  Serial.println("POWER");  update=true;currentpixel=0;on = !on; break;
        case 1:  Serial.println("VOL+");   update=true;bright+=brightinc;if(bright>255){bright=255;} break;
        case 2:  Serial.println("FUNC.");  update=true;clear();mode = !mode; break;
        case 4:  Serial.println("BACK");   update=true;if (mode){clear();modecount--;if(modecount<0){modecount=modeAmount-1;}}else{hue-=hueinc;if(hue<0){hue=65536;}} break;
        case 5:  Serial.println("PLAY");   break;
        case 6:  Serial.println("NEXT");   update=true;if (mode){clear();modecount++;if(modecount>modeAmount-1){modecount=0;}}else{hue+=hueinc;if(hue>65536){hue=0;}} break;
        case 8:  Serial.println("DOWN");   break;
        case 9:  Serial.println("VOL-");   update=true;bright-=brightinc;if(bright<0){bright=0;} break;
        case 10: Serial.println("UP");     break;
        case 12: Serial.println("num: 0"); break;
        case 13: Serial.println("EQ");     break;
        case 14: Serial.println("REPT.");  break;
        case 16: Serial.println("num: 1"); break;
        case 17: Serial.println("num: 2"); break;
        case 18: Serial.println("num: 3"); break;
        case 20: Serial.println("num: 4"); break;
        case 21: Serial.println("num: 5"); break;
        case 22: Serial.println("num: 6"); break;
        case 24: Serial.println("num: 7"); break;
        case 25: Serial.println("num: 8"); break;
        case 26: Serial.println("num: 9"); break;
        default: Serial.println(command);  break;
      }
    }
};

#endif
