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

#include <WS2812IR.hpp>

constexpr byte IRPin =  3;   // Signal Pin of IR receiver
IRrecv receiver(IRPin);

constexpr byte pixelCount = 40;  // Number of WS2812 pixels
constexpr byte PIN = 2;		 // Signal pin of WS2812 LEDs
Adafruit_NeoPixel pixels(pixelCount, PIN, NEO_GRB + NEO_KHZ800);

WS2812IR wsir(&receiver, &pixels, pixelCount);

void setup() {
  Serial.begin(115200);
  wsir.begin();
}

void loop() {
  wsir.strip(0,255,0,20); // Turn WS2812 strip on green, with a delay of 20ms between pixels
  delay(1000);
  wsir.strip(0,0,255,50); // Turn WS2812 strip on blue, with a delay of 50ms between pixels
  delay(1000);
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 200) { //loop through the entire hue range
    wsir.striphue(firstPixelHue,0); // // Turn WS2812 strip on the hue color from the i, with a delay of 0ms between pixels
  }
  delay(1000);
  wsir.off(0); // Turn WS2812 strip off, with a delay of 0ms between pixels
}
