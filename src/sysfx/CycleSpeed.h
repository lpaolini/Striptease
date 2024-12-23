#ifndef CycleSpeed_h
#define CycleSpeed_h

#include <Arduino.h>
#include "Fx.h"
#include "HarmonicMotion.h"
#include "Strip.h"
#include "State.h"

class CycleSpeed : public Fx {
    private:
        HarmonicMotion slider;

    public:
        CycleSpeed(Strip *strip, State *state);
        void reset();
        void loop();
};

#endif
