#ifndef SpeedMeter_h
#define SpeedMeter_h

#include <Arduino.h>
#include "Fx.h"
#include "HarmonicMotion.h"
#include "Strip.h"
#include "State.h"

class SpeedMeter : public Fx {
    private:
        HarmonicMotion slider;

    public:
        SpeedMeter(Strip *strip, State *state);
        void reset();
        void loop();
};

#endif
