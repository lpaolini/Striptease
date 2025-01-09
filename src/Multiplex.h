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
        ) {
            if (fx01 != nullptr) fxs.push_back(fx01);
            if (fx02 != nullptr) fxs.push_back(fx02);
            if (fx03 != nullptr) fxs.push_back(fx03);
            if (fx04 != nullptr) fxs.push_back(fx04);
            if (fx05 != nullptr) fxs.push_back(fx05);
            if (fx06 != nullptr) fxs.push_back(fx06);
            if (fx07 != nullptr) fxs.push_back(fx07);
            if (fx08 != nullptr) fxs.push_back(fx08);
            if (fx09 != nullptr) fxs.push_back(fx09);
            if (fx10 != nullptr) fxs.push_back(fx10);
            if (fx11 != nullptr) fxs.push_back(fx11);
            if (fx12 != nullptr) fxs.push_back(fx12);
            if (fx13 != nullptr) fxs.push_back(fx13);
            if (fx14 != nullptr) fxs.push_back(fx14);
            if (fx15 != nullptr) fxs.push_back(fx15);
            if (fx16 != nullptr) fxs.push_back(fx16);
            if (fx17 != nullptr) fxs.push_back(fx17);
            if (fx18 != nullptr) fxs.push_back(fx18);
            if (fx19 != nullptr) fxs.push_back(fx19);
            if (fx20 != nullptr) fxs.push_back(fx20);
        }

        void flush() override {
            for (Fx *fx : fxs) {
                fx->flush();
            }
        }

        void loop() {
            for (Fx *fx : fxs) {
                fx->loop();
            }
        }

        void reset() {
            for (Fx *fx : fxs) {
                fx->reset();
            }
        }

};

#endif
