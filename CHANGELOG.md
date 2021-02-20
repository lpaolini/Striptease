# version 1.2.3

## Hardware
- replaced cryptic PCB connector labels (J1, J2, J3) with more sensible ones

# version 1.2.2

## Bugfixes
- fixed various bugs triggered by corner cases, especially when using JoinedStrip

### HarmonicMotion
- fixed a bug caused by a wrong assignment

## Additions and improvements

### Multiplex
- refactored and increased the number of fx to 9.

### HarmonicMotion
- added methods for random positioning

### Bounce
- implemented a new simple fx

# version 1.2.1

## Bugfixes
- fixed various JoinedStrip bugs

# version 1.2.0

## BREAKING CHANGES

### AudioChannel
- trigger method has been removed and its functionality is now provided by AudioTrigger

### Trigger
- replaced by AudioTrigger

## Bugfixes

### Strip
- fixed paintNormalizedSize method

### JoinedStrip
- fixed paint method when indexFrom falls in strip 1 and indexTo falls in strip 2
- gap has been replaced with a StatefulStrip, so that its behavior is consistent with the visible portion 

## Additions and improvements

### Strip
- implemented *buffered()* method for creating a buffered version of a Strip, useful for those effects which alter the underlying Strip using blur, fade, shift, etc.

### SubStrip
- implemented a new Strip implementation for addressing a portion of another Strip

### AudioTrigger
- implemented for allowing beat detection over more than one loop, independently for concurrent effects
- the triggered method returns true if a beat was detected since the last call (or since the last call to the reset method)
- optionally, random triggers can be added (separately for signal detected or not), specifying the number of desired events per second

### AudioSensor
- implemented a separate low-pass-filtered RMS sensor for feeding the beat detector, which now responds to low frequencies only

### Fx
- implemented *strip*, *audioChannel* and *state* as Fx protected members, so that they don't need to be redefined for each effect implementation

### Matrix fx
- reimplemented without timers, for maximum smoothness

### PeakMeter fx
- reduced flashing on beat detected

### VU2 fx
- implemented new effect

# version 1.1.5

## Bugfixes
x
### AudioChannel
- fixed wrong number of FFT bins, now 128 (it was 40)

# version 1.1.4

## Bugfixes

### DeepSpace effect
- fixed bug causing freezing under certain circumstances
- set a minimum for number of items

## Additions and improvements

### AudioChannel
- allowed trigger to accumulate beat detection over multiple loops

### Controller
- added methods for presetting input (line or mic) and level

### Brightness
- reduced minimum brightness

### IRMP library
- updated to version 3.4.0

### ColorBar effect
- added extremely simple, static, single color effect

### SpeedMeter effect
- changed background color to pure blue to avoid color deviations

### Fire effect
- improved sound responsiveness

### Matrix effect
- improved sound responsiveness

### Strobe effect
- replaced color palette

# version 1.1.3

## HARDWARE FIX
Circuit for Teensy 4.1 has been fixed.

Previous version contained a serious flaw. Three pads, which looked grounded in the schematics, actually were not.
In particular, one of these caused the OE input ("output enable") of the level shifter (74HCT245) to be floating and thus in undefined state.

This caused the LED strip to freeze at random times.

In case you have already ordered your PCB and it's too late to cancel, the simplest fix is to scratch a bit the solder mask around those three pads and solder to the pin.
Given all unused copper is grounded, this would effectively connect those pins to ground, as shown in red in the picture (bottom view).

I apologize for this.

![PCB-fix](hardware/img/pcb-fix.jpg)

# version 1.1.2

## Additions and improvements

### Controller
- allow direct effect selection to enter play mode (e.g. when pressing a number on the remote)

### DeepSpace effect
- implemented direction changes

### Juggle
- implemented speed adjustment

# version 1.1.1

## Bugfixes

### JoinedStrip
- bypass buffer when distance is zero

# version 1.1.0

## BREAKING CHANGES

### HarmonicMotion
- dropped method **getNormalizedPosition**

### Strip

- turned into abstract class, with three concrete implementations:
	- __PhysicalStrip(CRGBSet &leds, uint16_t density)__
	- __ReversedStrip(Strip *strip)__
	- __JoinedStrip(Strip *strip1, Strip *strip2, uint16_t distance = 0)__
- removed public members **leds**, **count** and **length**
- renamed method **fill** to **paint**, with optional **add** argument
- renamed method **fullRainbow** to **rainbow**, with optional **deltaHue** argument
- removed method **randomPos** method, replaced by **random**
- renamed method **randomPosRange** to **randomInRange**
- renamed method **randomPosExclude** to **randomExclude**
- renamed method **centerPos** to **center**
- renamed method **lastPos** to **last**
- removed method **toPosition**
- renamed method **toNormalizedPosition** to **fromNormalizedPosition**

## Additions and improvements

### Strip
- replaced public members **leds**, **count** and **lenght** with appropriate public methods
- implemented method **blur**
- implemented method **first**
- implemented method **size**
- implemented method **paint** for single pixel
- implemented method **paintNormalized** for single pixel

### Photons (Fx)
- reimplemented using HarmonicMotion

# version 1.0.0

## First public release
