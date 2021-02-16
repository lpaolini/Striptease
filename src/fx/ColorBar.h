#ifndef ColorBar_h
#define ColorBar_h

#include <Arduino.h>
#include "Fx.h"
#include "Strip.h"
#include "State.h"

class ColorBar : public Fx {
    public:
        ColorBar(Strip *strip, State *state);
        void loop();
        void reset();
};

#endif
