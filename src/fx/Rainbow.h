#ifndef Rainbow_h
#define Rainbow_h

#include <Arduino.h>
#include "Fx.h"

class Rainbow : public Fx {
    private:
        uint8_t phase;

    public:
        Rainbow(Strip *strip, State *state, uint8_t phase = 0);
        void loop();
};

#endif
