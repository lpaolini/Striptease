#ifndef ColorBar_h
#define ColorBar_h

#include <Arduino.h>
#include "Fx.h"

class ColorBar : public Fx {
    public:
        ColorBar(Strip *strip, State *state);
        void loop();
};

#endif
