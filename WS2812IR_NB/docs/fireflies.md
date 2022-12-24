# fireflies

## The fireflies() Function

### Description

The `fireflies()` function is a mode that looks like fireflies!  Multiple random LEDs pulse for a random amount of time with random amounts of time between them.

### Syntax

```
WS2812IR_NB.fireflies(int amount=15, int timeon=1000, int timeoff=12000);
```

### Definition

This function takes 3 inputs.  The first (`amount`) sets the amount of fireflies.  Numbers above 20 seem to not work well, and the default is 15.  `timeon` is the max amount of time in milliseconds for the pixel to stay on.  `timeoff` is the max amount of time in milliseconds that the pixel stays off.
