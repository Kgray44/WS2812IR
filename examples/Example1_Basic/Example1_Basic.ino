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
