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
  wsir.chaseC(0, 255, 0, 100, 5000); // Turn WS2812 strip on slow chase, with a delay of 100ms between pixels, and be on for 10000ms
  wsir.off(10); // Turn WS2812 strip off, with a delay of 10ms between pixels
  wsir.lightningC(500, 40, 7000); // Turn WS2812 strip on lightning.  A delay of 500ms max between pixels flashing, and a delay of 40ms max time onpixels.  Also, it will be on for 20000ms
  wsir.off(0); // Turn WS2812 strip off, with a delay of 0ms between pixels
  wsir.messC(10, 5000); // Turn WS2812 strip on mess mode, with a delay of 10ms between pixels.  In this mode, random leds are changed with random timing, with random R, G, and B values.  Also, it will stay on for 10000ms
  wsir.off(0); // Turn WS2812 strip off, with a delay of 0ms between pixels
  wsir.rainbowC(2,7); // Turn WS2812 strip on rainbow mode for 2 loops, with a speed of 7.
  wsir.off(0); // Turn WS2812 strip off, with a delay of 0ms between pixels
  wsir.firefliesC(1,100,1200, 5000); 
  wsir.off(0); // Turn WS2812 strip off, with a delay of 0ms between pixels
  wsir.strobeC(255,0,0,100, 5000);
  wsir.off(0);
}
