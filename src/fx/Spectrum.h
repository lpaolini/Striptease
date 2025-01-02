#ifndef Spectrum_h
#define Spectrum_h

#include <Arduino.h>
#include <FastLED.h>
#include "audio/AudioSensor.h"
#include "Fx.h"
#include "Timer.h"
#include "HarmonicMotion.h"

class Spectrum : public Fx {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Black, CRGB::Blue, CRGB::Red, CRGB::Yellow);
        uint8_t segmentSize;

    public:
        Spectrum(Strip *strip, AudioChannel *audioChannel);
        void loop();
};

#endif
