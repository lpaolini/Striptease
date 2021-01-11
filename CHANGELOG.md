# version 1.1.0

## BREAKING CHANGES

### HarmonicMotion
- dropped method **getNormalizedPosition**

### Strip
- removed public member **length**
- changed visibility of public members **leds**, **count** to private
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
