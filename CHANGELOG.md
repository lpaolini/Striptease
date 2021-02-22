# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

Nothing.

## [1.2.4] (2021-02-22)
### Added
- Adopted [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [1.2.3]

### Changed
- Replaced cryptic PCB connector labels (J1, J2, J3, etc.) with more human-frendly ones (POWER, LEDS, IR-RECV, etc).

## [1.2.2]

### Fixed
- Fixed various bugs triggered by corner cases, especially when using JoinedStrip.
- Fixed a bug in HarmonicMotion caused by a wrong assignment.

### Added
- `Multiplex`
    - Increased the number of multiplexed effects to 9.
- `HarmonicMotion`
    - Added methods for random positioning:
        - `setFixedPointRandomPosition()`
        - `setRandomPosition()`
- Implemented new simple effect `Bounce`.

## [1.2.1]

### Fixed
- `JoinedStrip`
    - Fixed various bugs.

## [1.2.0]

### Changed
- `AudioChannel`
    - Method `trigger` has been removed and its functionality is now provided by `AudioTrigger`.
- `Trigger`
    - Replaced by `AudioTrigger`.

### Fixed
- `Strip`
    - Fixed `paintNormalizedSize` method.
- `JoinedStrip`
    - Fixed `paint` method when indexFrom falls in strip 1 and indexTo falls in strip 2.
    - Gap has been replaced with a `StatefulStrip`, so that its behavior is consistent with the visible portion of the strip.

### Added
- `Strip`
    - Implemented `buffered` method for creating a buffered version of a Strip, useful for those effects which alter the underlying Strip using blur, fade, shift, etc.
- Implemented new Strip implementation `SubStrip` for addressing a portion of another Strip.
- Implemented `AudioTrigger` for allowing beat detection over more than one loop, independently for concurrent effects.
    - The `triggered` method returns true if a beat was detected since the last call (or since the last call to the reset method).
    - Optionally, random triggers can be added (separately for signal detected or not), specifying the number of desired events per second.
- `AudioSensor`
    - implemented a separate low-pass-filtered RMS sensor for feeding the beat detector, which now responds to low frequencies only.
- `Fx`
    - implemented `strip`, `audioChannel` and `state` as protected members, so that they don't need to be redefined for each effect implementation.
- `Matrix` fx
    - Reimplemented without timers, for maximum smoothness.
- `PeakMeter` fx
    - Reduced flashing on beat detected.
- `VU2` fx
    - Implemented new effect.

## [1.1.5]

### Fixed
- `AudioChannel`
    - Fixed wrong number of FFT bins, now 128 (it was 40).

## [1.1.4]

### Fixed
- `DeepSpace` fx
    - Fixed bug causing freezing under certain circumstances.
    - Set a minimum for number of items (instead of zero).

### Added
- `AudioChannel`
    - Allowed trigger to accumulate beat detection over multiple loops.
- `Controller`
    - Added methods for presetting input (line or mic) and level.
- `Brightness`
    - Reduced minimum brightness.
- IRMP library
    - Updated to version 3.4.0.
- `ColorBar` fx
    - Added extremely simple, static, single color effect.
- `SpeedMeter` fx
    - Changed background color to pure blue to avoid color deviations.
- `Fire` fx
    - Improved sound responsiveness.
- `Matrix` fx
    - Improved sound responsiveness.
- `Strobe` fx
    - Replaced color palette.

## [1.1.3]

### Fixed
- Circuit for Teensy 4.1 has been fixed.

    Previous version contained a serious flaw. Three pads, which looked grounded in the schematics, actually were not.
    In particular, one of these caused the OE input ("output enable") of the level shifter (74HCT245) to be floating and thus in undefined state.

    This caused the LED strip to freeze at random times.

    In case you have already ordered your PCB and it's too late to cancel, the simplest fix is to scratch a bit the solder mask around those three pads and solder to the pin.
    Given all unused copper is grounded, this would effectively connect those pins to ground, as shown in red in the picture (bottom view).

    I apologize for this.

    ![PCB-fix](hardware/img/pcb-fix.jpg)

## [1.1.2]

### Added
- `Controller`
    - Allowed direct effect selection to enter play mode (e.g. when pressing a number on the remote).
- `DeepSpace` fx
    - implemented direction changes.
- `Juggle`
    - Implemented speed adjustment.

## [1.1.1]

### Fixed
- `JoinedStrip`
    - Bypassed buffer when distance is zero.

## [1.1.0]

### Changed
- `HarmonicMotion`
    - Dropped method `getNormalizedPosition`.
- `Strip`
    - Turned into abstract class, with three concrete implementations:
        - `PhysicalStrip(CRGBSet &leds, uint16_t density)`
        - `ReversedStrip(Strip *strip)`
        - `JoinedStrip(Strip *strip1, Strip *strip2, uint16_t distance = 0)`
    - Replaced public members `leds`, `count` and `lenght` with public getters.
    - Renamed method `fill` to `paint`, with optional `add` argument.
    - Renamed method `fullRainbow` to `rainbow`, with optional `deltaHue` argument.
    - Removed method `randomPos` method, replaced by `random`.
    - Renamed method `randomPosRange` to `randomInRange`.
    - Renamed method `randomPosExclude` to `randomExclude`.
    - Renamed method `centerPos` to `center`.
    - Renamed method `lastPos` to `last`.
    - Removed method `toPosition`.
    - Renamed method `toNormalizedPosition` to `fromNormalizedPosition`.
- `Photons` fx
    - Reimplemented using HarmonicMotion.

### Added
- `Strip`
    - Implemented method `blur`.
    - Implemented method `first`.
    - Implemented method `size`.
    - Implemented method `paint` for single pixel.
    - Implemented method `paintNormalized` for single pixel.

## [1.0.0]

### First public release
