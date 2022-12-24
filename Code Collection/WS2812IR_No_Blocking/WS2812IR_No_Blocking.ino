/*************************************************************
File Name: WS2812IR_No_Blocking.ino
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

bool testIR = false;//true or false

#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

#define modeAmount 5
#define hueinc 1000
#define brightinc 20

#define RECV_PIN  3
#define PIN       2
#define NUMPIXELS 180

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

unsigned long hue = 0;

int bright = 127;
int modecount = 0;
bool mode = 0;
bool on = true;
bool update = true;
int currentpixel=0;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  irrecv.enableIRIn();
  irrecv.blink13(true);

  pixels.begin();
}

void loop() {
  listenIR();
  takeStep();
}

void listenIR() {
  if (irrecv.decode()) {
    handleKey();
    irrecv.resume();  // Receive the next value
  }
}

void takeStep(){
  if (on){
    if (!mode){
      if (update){
        currentpixel++;
        pixels.setBrightness(bright);
        pixels.setPixelColor(currentpixel, pixels.gamma32(pixels.ColorHSV(hue)));
        pixels.show();
        if (currentpixel>=NUMPIXELS){
          update=false;
          currentpixel=0;
        }
      }
    }
  }
  else {
    if (update){
      currentpixel++;
      pixels.setPixelColor(currentpixel, pixels.Color(0, 0, 0));
      pixels.show();
      if (currentpixel>=NUMPIXELS){
        currentpixel=0;
        update=false;
      }
    }
  }
}

void handleKey() {
  uint16_t command;
  if (irrecv.decodedIRData.protocol == 7 && !testIR){
    command = irrecv.decodedIRData.command;
  }
  if (testIR){
    Serial.println(command);
    return;
  }
  Serial.println("Protocol:" + String(irrecv.decodedIRData.protocol));

  switch (command) {
    case 0:  Serial.println("POWER");  update=true;currentpixel=0;on = !on;     break;
    case 1:  Serial.println("VOL+");   update=true;bright+=brightinc;if(bright>255){bright=255;} break;
    case 2:  Serial.println("FUNC.");  mode = !mode; break;
    case 4:  Serial.println("BACK");   update=true;if (mode){modecount--;if(modecount<0){modecount=0;}}else{hue-=hueinc;if(hue<0){hue=65536;}} break;
    case 5:  Serial.println("PLAY");   break;
    case 6:  Serial.println("NEXT");   update=true;if (mode){modecount++;if(modecount>modeAmount){modecount=modeAmount;}}else{hue+=hueinc;if(hue>65536){hue=0;}} break;
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
