/*************************************************************
File Name: WS2812IR.hpp
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

#ifndef WS2812IR_h
#define WS2812IR_h

#include "Arduino.h"
#include <IRremote.hpp>
#include <Adafruit_NeoPixel.h>

class WS2812IR
{
  public:
    IRrecv* receiver;
    Adafruit_NeoPixel *pixels;
    size_t pixelsCount;

    WS2812IR(IRrecv* r, Adafruit_NeoPixel *p, size_t n) : receiver(r), pixels(p), pixelsCount(n) {}

    void begin() {
      receiver->enableIRIn(); // Start the receiver
      pixels->begin();
      strip(0,0,0,0);
    }

    void listenIR() {
      if (receiver->decode()) {
        handleKey();
        receiver->resume();  // Receive the next value
      }
    }

    void off(int speed){
      for(int i=0; i<pixelsCount; i++) {
        pixels->setPixelColor(i, pixels->Color(0, 0, 0));
        pixels->show();
        delay(speed);
      }
    }
    
    void strip(int R, int G, int B, int speed)
    {
      for(int i=0; i<pixelsCount; i++) {
        pixels->setPixelColor(i, pixels->Color(R, G, B));
        pixels->show();
        delay(speed);
      }
    }

    void striphue(int hue, int speed)
    {
      for(int i=0; i<pixelsCount; i++) {
        pixels->setPixelColor(i, pixels->gamma32(pixels->ColorHSV(hue)));
        pixels->show();
        delay(speed);
      }
    }

    void rainbow(int speed)
    {
      // Hue of first pixel runs 5 complete loops through the color wheel.
      // Color wheel has a range of 65536 but it's OK if we roll over, so
      // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
      // means we'll make 5*65536/256 = 1280 passes through this outer loop:
      while (!receiver->decode()){ //IR interrupt
        for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
          for(int i=0; i<pixels->numPixels(); i++) { // For each pixel in strip...
            // Offset pixel hue by an amount to make one full revolution of the
            // color wheel (range of 65536) along the length of the strip
            // (strip.numPixels() steps):
            int pixelHue = firstPixelHue + (i * 65536L / pixels->numPixels());
            // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
            // optionally add saturation and value (brightness) (each 0 to 255).
            // Here we're using just the single-argument hue variant. The result
            // is passed through strip.gamma32() to provide 'truer' colors
            // before assigning to each pixel:
            pixels->setPixelColor(i, pixels->gamma32(pixels->ColorHSV(pixelHue)));
            if (receiver->decode()){return;} //IR interrupt
          }
          pixels->show(); // Update strip with new contents
          delay(speed);  // Pause for a moment
        }
      }
      delay(200);
      receiver->resume();  // Receive the next value
    }

    void rainbowC(int loopnumber, int speed)
    {
      // Hue of first pixel runs 5 complete loops through the color wheel.
      // Color wheel has a range of 65536 but it's OK if we roll over, so
      // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
      // means we'll make 5*65536/256 = 1280 passes through this outer loop:
      for(long firstPixelHue = 0; firstPixelHue < loopnumber*65536; firstPixelHue += 256) {
        for(int i=0; i<pixels->numPixels(); i++) { // For each pixel in strip...
          // Offset pixel hue by an amount to make one full revolution of the
          // color wheel (range of 65536) along the length of the strip
          // (strip.numPixels() steps):
          int pixelHue = firstPixelHue + (i * 65536L / pixels->numPixels());
          // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
          // optionally add saturation and value (brightness) (each 0 to 255).
          // Here we're using just the single-argument hue variant. The result
          // is passed through strip.gamma32() to provide 'truer' colors
          // before assigning to each pixel:
          pixels->setPixelColor(i, pixels->gamma32(pixels->ColorHSV(pixelHue)));
          if (receiver->decode()){return;} //IR interrupt
        }
        pixels->show(); // Update strip with new contents
        delay(speed);  // Pause for a moment
      }
    }
    
    void lightning(int ledoffdelay,int ledondelay){//recommended lower delays for a longer strip
      while (!receiver->decode()){ //IR interrupt
        int pixelN = random(1,pixelsCount);
        pixels->setPixelColor(pixelN, pixels->Color(255, 255, 255)); //white lightning
        pixels->show();
        delay(random(4,ledondelay));
        pixels->setPixelColor(pixelN, pixels->Color(0, 0, 0));
        pixels->show();
        delay(random(10,ledoffdelay));
      }
      delay(200);
      receiver->resume();  // Receive the next value
    }

    void lightningC(int ledoffdelay, int ledondelay, int time){//recommended lower delays for a longer strip
      unsigned long startmillis=millis();
      while ((millis() - startmillis) < time){ //check time
        int pixelN = random(1,pixelsCount);
        pixels->setPixelColor(pixelN, pixels->Color(255, 255, 255)); //white lightning
        pixels->show();
        delay(random(4,ledondelay));
        pixels->setPixelColor(pixelN, pixels->Color(0, 0, 0));
        pixels->show();
        delay(random(10,ledoffdelay));
      }
    }
    
    void chase(int R,int G,int B,int speed){
      while (!receiver->decode()){//IR interrupt
        for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
          pixels->clear();         //   Set all pixels in RAM to 0 (off)
          // 'c' counts up from 'b' to end of strip in steps of 3...
          for(int c=b; c<pixelsCount; c += 3) {
            pixels->setPixelColor(c, pixels->Color(R,G,B)); // Set pixel 'c' to value 'color'
          }
          pixels->show(); // Update strip with new contents
          delay(speed);  // Pause for a moment
        }
      }
      delay(200);
      receiver->resume();  // Receive the next value
    }

    void chaseC(int R, int G, int B,int speed, int time){
      unsigned long startmillis=millis();
      while ((millis() - startmillis) < time){ //check time
        for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
          pixels->clear();         //   Set all pixels in RAM to 0 (off)
          // 'c' counts up from 'b' to end of strip in steps of 3...
          for(int c=b; c<pixelsCount; c += 3) {
            pixels->setPixelColor(c, pixels->Color(R,G,B)); // Set pixel 'c' to value 'color'
          }
          pixels->show(); // Update strip with new contents
          delay(speed);  // Pause for a moment
        }
      }
    }

    void pulse(int R, int G, int B, int speed){
      int pixel=0;
      while (!receiver->decode()){
        for (int i=0;i<5;i++){
          pixel++;
          if (pixel >= pixelsCount){pixel=0;}
          pixels->setPixelColor(pixel, pixels->Color(0,(G/10)*i,0));
          pixels->show();
        }
        for (int i=5;i>0;i--){
          pixel++;
          if (pixel >= pixelsCount){pixel=0;}
          pixels->setPixelColor(pixel, pixels->Color(0,(G/10)*i,0));
          pixels->show();
        }
        for (int i=0;i<10;i++){
          pixel++;
          if (pixel >= pixelsCount){pixel=0;}
          pixels->setPixelColor(pixel, pixels->Color(0,0,0));
          pixels->show();
        }
        pixel++;
        if (pixel >= pixelsCount){pixel=0;}
        delay(speed);
      }
      delay(200);
      receiver->resume();  // Receive the next value
    }
    
    void pulseC(int R, int G, int B, int speed, int time){
      int pixel=0;
      unsigned long startmillis=millis();
      while ((millis() - startmillis) < time){ //check time
        for (int i=0;i<5;i++){
          pixel++;
          if (pixel >= pixelsCount){pixel=0;}
          pixels->setPixelColor(pixel, pixels->Color(0,(G/10)*i,0));
          pixels->show();
        }
        for (int i=5;i>0;i--){
          pixel++;
          if (pixel >= pixelsCount){pixel=0;}
          pixels->setPixelColor(pixel, pixels->Color(0,(G/10)*i,0));
          pixels->show();
        }
        for (int i=0;i<10;i++){
          pixel++;
          if (pixel >= pixelsCount){pixel=0;}
          pixels->setPixelColor(pixel, pixels->Color(0,0,0));
          pixels->show();
        }
        pixel++;
        if (pixel >= pixelsCount){pixel=0;}
        delay(speed);
      }
    }

    void mess(int speed){
      while (!receiver->decode()){//IR interrupt
        int R = random(1,255);
        int G = random(1,255);
        int B = random(1,255);
        int p = random(1,pixelsCount);
        int t = random(1,speed);
        pixels->setPixelColor(p, pixels->Color(R,G,B));
        pixels->show();
        delay(t);
      }
      delay(200);
      receiver->resume();  // Receive the next value
    }
    
    void messC(int speed, int time){
      unsigned long startmillis=millis();
      while ((millis() - startmillis) < time){ //check time
        int R = random(1,255);
        int G = random(1,255);
        int B = random(1,255);
        int p = random(1,pixelsCount);
        int t = random(1,speed);
        pixels->setPixelColor(p, pixels->Color(R,G,B));
        pixels->show();
        delay(t);
      }
    }
    
    void fireflies(int ontimespeed, int ontime, int delaytime){
      while (!receiver->decode()){ //IR interrupt
        int pixel = random(1,pixelsCount);
        int d = random(10,delaytime);
        for (int i=0;i<255;i++){
          pixels->setPixelColor(pixel, pixels->Color(map(i,0,255,0,255), map(i,0,255,0,255), map(i,0,255,0,175)));
          pixels->show();
          delay(ontimespeed);
        }
        delay(ontime);
        for (int i=0;i<255;i++){
          pixels->setPixelColor(pixel, pixels->Color(map(i,0,255,255,0), map(i,0,255,255,0), map(i,0,255,100,0)));
          pixels->show();
          delay(ontimespeed);
        }
	pixels->setPixelColor(pixel, pixels->Color(0, 0, 0));
        pixels->show();
        delay(d);
      }
      delay(200);
      receiver->resume();  // Receive the next value
    }

    void firefliesC(int ontimespeed, int ontime, int delaytime, int time){
      unsigned long startmillis=millis();
      while ((millis() - startmillis) < time){ //check time
        int pixel = random(1,pixelsCount);
        int d = random(10,delaytime);
        for (int i=0;i<255;i++){
          pixels->setPixelColor(pixel, pixels->Color(map(i,0,255,0,255), map(i,0,255,0,255), map(i,0,255,0,175)));
          pixels->show();
          delay(ontimespeed);
        }
        delay(ontime);
        for (int i=0;i<255;i++){
          pixels->setPixelColor(pixel, pixels->Color(map(i,0,255,255,0), map(i,0,255,255,0), map(i,0,255,100,0)));
          pixels->show();
          delay(ontimespeed);
        }
	pixels->setPixelColor(pixel, pixels->Color(0, 0, 0));
        pixels->show();
        delay(d);
      }
      delay(200);
      receiver->resume();  // Receive the next value
    }

    void strobe(int R, int G, int B, int speed){
      while (!receiver->decode()){//IR interrupt
        for (int i=0;i<pixelsCount;i+=6){
          for (int p=0;p<3;p++){
            pixels->setPixelColor(i+p, pixels->Color(R,G,B));
            pixels->show();
          }
          for (int p=3;p<6;p++){
            pixels->setPixelColor(i+p, pixels->Color(0,0,0));
            pixels->show();
          }
        }
        delay(speed);
        for (int i=0;i<pixelsCount;i+=6){
          for (int p=0;p<3;p++){
            pixels->setPixelColor(i+p, pixels->Color(0,0,0));
            pixels->show();
          }
          for (int p=3;p<6;p++){
            pixels->setPixelColor(i+p, pixels->Color(R,G,B));
            pixels->show();
          }
        }
        delay(speed);
      }
      receiver->resume();  // Receive the next value
    }

    void strobeC(int R, int G, int B, int speed, int time){
      unsigned long startmillis=millis();
      while ((millis() - startmillis) < time){ //check time
        for (int i=0;i<pixelsCount;i+=6){
          for (int p=0;p<3;p++){
            pixels->setPixelColor(i+p, pixels->Color(R,G,B));
            pixels->show();
          }
          for (int p=3;p<6;p++){
            pixels->setPixelColor(i+p, pixels->Color(0,0,0));
            pixels->show();
          }
        }
        delay(speed);
        for (int i=0;i<pixelsCount;i+=6){
          for (int p=0;p<3;p++){
            pixels->setPixelColor(i+p, pixels->Color(0,0,0));
            pixels->show();
          }
          for (int p=3;p<6;p++){
            pixels->setPixelColor(i+p, pixels->Color(R,G,B));
            pixels->show();
          }
        }
        delay(speed);
      }
      receiver->resume();  // Receive the next value
    }

  private:
    void handleKey() {
      uint16_t command = receiver->decodedIRData.command;
      switch (command) {
        case 162: Serial.println("POWER");  strip(0,255,0,20);   break;
        case 226: Serial.println("MENU");   strip(127,255,0,20); break;;
        case  34: Serial.println("TEST");   strip(255,255,0,20); break;
        case   2: Serial.println("PLUS");   strip(255,127,0,20); break;
        case 194: Serial.println("BACK");   strip(255,0,0,20);   break;
        case 224: Serial.println("PREV.");  break;
        case 168: Serial.println("PLAY");   break;
        case 144: Serial.println("NEXT");   break;
        case 104: Serial.println("num: 0"); break;
        case 152: Serial.println("MINUS");  break;
        case 176: Serial.println("key: C"); break;
        case  48: Serial.println("num: 1"); break;
        case  24: Serial.println("num: 2"); break;
        case 122: Serial.println("num: 3"); break;
        case  16: Serial.println("num: 4"); break;
        case  56: Serial.println("num: 5"); break;
        case  90: Serial.println("num: 6"); break;
        case  66: Serial.println("num: 7"); break;
        case  74: Serial.println("num: 8"); break;
        case  82: Serial.println("num: 9"); break;
        default:  Serial.println(command);  break;
      }
    }
};

#endif
