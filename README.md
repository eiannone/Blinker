# Blinker

This library is an asyncronous led blinker for Arduino framework, designed to not interfere with other code which controls the same led.
It supports three operational modes:
- *NORMAL*: Led switches ON and then OFF
- *INVERT*: Invert current led state, so if it's ON, it blinks switching OFF and then ON
- *SKIP_IF_ON*: Blinks only if led is currently OFF, otherwise it leaves it ON.

You can call `start()` method, passing *ON* and *OFF* duration, and number of repetitions, or you can call `once()` method, to blink once.

## Examples
```
#include "Arduino.h"
#include "Blinker.h"

Blinker blinker(LED_BUILTIN);

// Blinks three times, staying 100 ms ON and 400 ms OFF
blinker.start(100, 400, 3);

// Blinks once for 300 msec
blinker.once(300); 
```