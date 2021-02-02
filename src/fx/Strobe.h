#ifndef Strobe_h
#define Strobe_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "Fx.h"
#include "State.h"
#include "Timer.h"

class Strobe : public Fx {
    private:
        const uint8_t SEGMENT_SIZE = 10;
        const CRGBPalette16 PALETTE = CRGBPalette16(PartyColors_p);
        Strip *strip;
        AudioChannel *audioChannel;
        State *state;
        Timer timer = Timer(100);
        
    public:
        Strobe(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
