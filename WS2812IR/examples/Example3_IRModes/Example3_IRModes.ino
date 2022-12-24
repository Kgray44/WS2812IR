/*************************************************************
File Name: Example3_IRModes.ino
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

#include <WS2812IR.hpp>

constexpr byte IRPin =  3;   // Signal Pin of IR receiver
IRrecv receiver(IRPin);

constexpr byte pixelCount = 40;
constexpr byte PIN = 2;
Adafruit_NeoPixel pixels(pixelCount, PIN, NEO_GRB + NEO_KHZ800);

constexpr byte stripPin = 3;
WS2812IR wsir(&receiver, &pixels, pixelCount);

void setup() {
  pixels.begin();
  Serial.begin(115200);
  wsir.begin();
}

void loop() {
  wsir.chase(0, 255, 0, 100); // Turn WS2812 strip on slow chase, with a delay of 100ms between pixelspixels
  wsir.off(10); // Turn WS2812 strip off, with a delay of 10ms between pixels
  wsir.lightning(500,40); // Turn WS2812 strip on lightning.  A delay of 500ms max between pixels flashing, and a delay of 40ms max time onpixels
  wsir.listenIR(); // Check which code was pressed to turn the lightning off
  wsir.off(0); // Turn WS2812 strip off, with a delay of 0ms between pixels
  wsir.mess(10); // Turn WS2812 strip on mess mode, with a delay of 10ms between pixels.  In this mode, random leds are changed with random timing, with random R, G, and B values
  wsir.off(0); // Turn WS2812 strip off, with a delay of 0ms between pixels
  wsir.rainbow(7);
  wsir.listenIR(); // Check which code was pressed to turn the lightning off
  wsir.off(0);
  wsir.fireflies(1,100,700);
  wsir.off(0);
  wsir.strobe(255,0,0,100);
  wsir.listenIR(); // Check which code was pressed to turn the lightning off
  wsir.off(0);
}
