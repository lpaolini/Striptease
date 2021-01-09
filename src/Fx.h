#ifndef Fx_h
#define Fx_h

#include <Arduino.h>
#include "Strip.h"

class Fx {
    public:
        Fx() {};
        void clear(Strip *strip) {
            strip->off();
        }
        virtual void loop();
        virtual void reset();
};

#endif
