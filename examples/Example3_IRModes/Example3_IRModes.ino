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
