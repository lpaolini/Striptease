#ifndef Photons_h
#define Photons_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "Fx.h"
#include "Photon.h"
#include "State.h"

class Photons: public Fx {
    private:
        static const uint8_t NUM_PHOTONS = 6;
        Strip *strip;
        State *state;
        AudioChannel *audioChannel;
        Photon photons[NUM_PHOTONS];

    public:
        Photons(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
