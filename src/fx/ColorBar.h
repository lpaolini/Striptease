#ifndef ColorBar_h
#define ColorBar_h

#include <Arduino.h>
#include "Fx.h"
#include "Strip.h"
#include "State.h"

class ColorBar : public Fx {
    private:
        Strip *strip;
        State *state;

    public:
        ColorBar(Strip *strip, State *state);
        void loop();
        void reset();
};

#endif
