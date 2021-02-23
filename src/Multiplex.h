#ifndef Multiplex_h
#define Multiplex_h

#include <Arduino.h>
#include <FastLED.h>
#include <vector>
#include "Fx.h"

class Multiplex : public Fx {
    private:
        std::vector<Fx *> fxs;

    public:
        Multiplex(
            Fx *fx1 = nullptr,
            Fx *fx2 = nullptr,
            Fx *fx3 = nullptr,
            Fx *fx4 = nullptr,
            Fx *fx5 = nullptr,
            Fx *fx6 = nullptr,
            Fx *fx7 = nullptr,
            Fx *fx8 = nullptr,
            Fx *fx9 = nullptr
        );
        void loop();
        void reset();
        void flush() override;
};

#endif
