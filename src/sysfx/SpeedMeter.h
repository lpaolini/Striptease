#ifndef SpeedMeter_h
#define SpeedMeter_h

#include <Arduino.h>
#include "Fx.h"
#include "Strip.h"
#include "State.h"

class SpeedMeter : public Fx {
    private:
        Strip *strip;
        State *state;

    public:
        SpeedMeter(Strip *strip, State *state);
        void loop();
        void reset();
};

#endif
