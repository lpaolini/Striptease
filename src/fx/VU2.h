#ifndef VU2_h
#define VU2_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Timer.h"
#include "AudioChannel.h"
#include "HarmonicMotion.h"

class VU2 : public Fx {
    private:
        uint16_t size;
        float elasticConstant;
        HarmonicMotion peak;
        void resetPeak();
        
    public:
        VU2(Strip *strip, AudioChannel *audioChannel, uint16_t size = 10, float elasticConstant = 1000);
        void loop();
        void reset();
};

#endif
