#ifndef CycleSpeed_h
#define CycleSpeed_h

#include <Arduino.h>
#include "Fx.h"
#include "Strip.h"
#include "State.h"

class CycleSpeed : public Fx {
    public:
        CycleSpeed(Strip *strip, State *state);
        void loop();
        void reset();
};

#endif
