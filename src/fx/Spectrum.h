#ifndef Spectrum_h
#define Spectrum_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "Fx.h"
#include "Timer.h"
#include "HarmonicMotion.h"

class Spectrum : public Fx {
    public:
        Spectrum(Strip *strip, AudioChannel *audioChannel);
        void loop();
        void reset();
};

#endif
