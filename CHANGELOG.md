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
