#ifndef Multiplex_h
#define Multiplex_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"

class Multiplex : public Fx {
    private:
        Fx *fx1;
        Fx *fx2;
        Fx *fx3;
        Fx *fx4;
        Fx *fx5;
        Fx *fx6;

    public:
        Multiplex(
            Fx *fx1 = nullptr,
            Fx *fx2 = nullptr,
            Fx *fx3 = nullptr,
            Fx *fx4 = nullptr,
            Fx *fx5 = nullptr,
            Fx *fx6 = nullptr
        );
        void loop();
        void reset();
};

#endif
