#ifndef Multiplex_h
#define Multiplex_h

#include <vector>
#include "Fx.h"

class Multiplex : public Fx {
    private:
        std::vector<Fx *> fxs;

    public:
        Multiplex(
            Fx *fx01 = nullptr,
            Fx *fx02 = nullptr,
            Fx *fx03 = nullptr,
            Fx *fx04 = nullptr,
            Fx *fx05 = nullptr,
            Fx *fx06 = nullptr,
            Fx *fx07 = nullptr,
            Fx *fx08 = nullptr,
            Fx *fx09 = nullptr,
            Fx *fx10 = nullptr,
            Fx *fx11 = nullptr,
            Fx *fx12 = nullptr,
            Fx *fx13 = nullptr,
            Fx *fx14 = nullptr,
            Fx *fx15 = nullptr,
            Fx *fx16 = nullptr,
            Fx *fx17 = nullptr,
            Fx *fx18 = nullptr,
            Fx *fx19 = nullptr,
            Fx *fx20 = nullptr
        );
        void loop();
        void reset();
        void flush() override;
};

#endif
