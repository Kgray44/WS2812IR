/*************************************************************
File Name: Example1_Basic.ino
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

#include "WS2812IR_NB.hpp"

int hueinc = 1000; //increment for increasing/decreasing hue; example: if hue=250, 1 positive step will = 1250
int brightinc = 20; //increment for increasing/decreasing brightness

constexpr byte IRPin =  3;   // Signal Pin of IR receiver
IRrecv receiver(IRPin);

constexpr byte pixelCount = 180;  //number of pixels
constexpr byte PIN = 2;  //WS2812 Strip pin
Adafruit_NeoPixel pixels(pixelCount, PIN, NEO_GRB + NEO_KHZ800);

WS2812IR_NB wsir(&receiver, &pixels, pixelCount);

void setup() {
  Serial.begin(9600);
  wsir.begin();
}

void loop() {
  wsir.listenIR(); //listen for IR and change values accordingly
  wsir.takeStep(); //take one step; i.e. adjust the LED strip according to the IR
}
