# lightning

## The lightning() Function

### Description

The `lightning()` function is a mode that makes random pixels flash with a random amount of time between.

### Syntax

```
WS2812IR_NB.lightning(int ledoffdelay=500, int ledondelay=50);
```

### Definition

This function takes two values.  The `ledoffdelay` value is the max amount of time in milliseconds between flashes (the default is 500, 0.5 seconds).  The `ledondelay` value is the max amount of time in milliseconds between when the pixel is turned on, wd when it is turned off (the amount of time the pixel is on during the flash).  The default is set to 50ms.
