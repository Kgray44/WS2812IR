# WS2812IR Library and WS2812 with IR Code Collection

## WS2812IR Library

This library is for using WS2812 LEDs with a IR Remote!

I hope to do a complete do-over of this library soon, as all of it's code is blocking.  This will not seem to be an issue, besides a delay of up to 2 seconds from when an IR remote button is pressed.  The library, as is though, works and functions correctly!

### Dependencies

This library requires IRremote.h and Adafruit_NeoPixel.h libraries to be installed before use.


## WS2812IR Code Collection

Check out the WS2812IR_No_Blocking.ino sketch!  It doesn't utilise the library, and it's code is completely non-blocking.

Newly added: WS2812IR_No_Blocking_with_Modes.ino is a new sketch that includes 4 "modes", along with the basic color changing and brightness altering of the previous none blocking sketch!  The "modes" are:
* Strobe (3 LEDs flash, then switch to the other 3)
* Chase (single LED pattern, appears to be going along the strip)
* Lightning (looks like lightning, random pixels flash with random times between)
* Rainbow (a gliding rainbow)
* Fireflies (multiple pixels randomly pulse, looks like fireflies!)

----------

*More coming soon...*


Big thanks to @J-M-L over at Arduino Forum!

https://forum.arduino.cc/t/can-i-include-a-library-in-my-own-library/1066814
