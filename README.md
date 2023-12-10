# WS2812IR Library and WS2812 with IR Code Collection

## WS2812IR Library

This library is for using WS2812 LEDs with a IR Remote!

I hope to do a complete do-over of this library soon, as all of it's code is blocking.  This will not seem to be an issue, besides a delay of up to 2 seconds from when an IR remote button is pressed.  The library, as is though, works and functions correctly!

Check the docs for more information.

*Edit: Do-over complete!*

### Dependencies

This library requires IRremote.h and Adafruit_NeoPixel.h libraries to be installed before use.

## WS2812IR_NB Library

This library is for using WS2812 LEDs with a IR Remote!

This version ("_NB") is a Non-Blocking version.  So it runs very fast, resulting in no delay between a button press on the remote, and the response by the LEDs.

This also means that there is no delay between the updating of the first pixel on a strip, and the last pixel!!!  This is very noticeable on longer strips, and results in a cascade effect, rather than all of the pixels being changed at once.

Check the docs for more information.

### Dependencies

This library requires IRremote.h and Adafruit_NeoPixel.h libraries to be installed before use.

## WS2812IR Code Collection

Check out the WS2812IR_No_Blocking.ino sketch!  It doesn't utilise the library, and it's code is completely non-blocking.

WS2812IR_No_Blocking_with_Modes.ino is a new sketch that includes 4 "modes", along with the basic color changing and brightness altering of the previous none blocking sketch!  The "modes" are:
* Strobe (3 LEDs flash, then switch to the other 3)
* Chase (single LED pattern, appears to be going along the strip and takes a hue value)
* ChaseC (single LED pattern, appears to be going along the strip and takes a RGB value)
* Lightning (looks like lightning, random pixels flash with random times between)
* Rainbow (a gliding rainbow)
* Fireflies (multiple pixels randomly pulse, looks like fireflies!)
* Popcorn (red pixels that suddenly randomly turn white; red kernel popcorn popping)

**Newly added**: WS2812IR_NB-Christmas.ino is a brand new sketch that utilizes my _NB library!  It includes demonstrations on multicolored single functions, and also stacked functions.  It shows how to run multiple functions one aft another based on a simple timer setup, so there is not a single "delay" in the entire sketch or library!!

*Note*

To change the color of the LEDs running in a function, just call "wsir.hue = 3000;" (takes a hue value from 0 to 65536).  This will set the color for the next function(s) that you run.  The color can also be reset while the function is running, resulting in multicolored functions (take a look at "WS2812IR_NB-Christmas.ino").  Multiple functions can even be run at the same time... basically stacking effects!

----------

*More coming soon...*


Big thanks to @J-M-L over at Arduino Forum!

https://forum.arduino.cc/t/can-i-include-a-library-in-my-own-library/1066814
