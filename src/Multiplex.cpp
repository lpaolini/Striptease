#include "Multiplex.h"

Multiplex::Multiplex(Fx *fx1, Fx *fx2, Fx *fx3, Fx *fx4, Fx *fx5, Fx *fx6, Fx *fx7, Fx *fx8, Fx *fx9) {
    if (fx1 != nullptr) fxs.push_back(fx1);
    if (fx2 != nullptr) fxs.push_back(fx2);
    if (fx3 != nullptr) fxs.push_back(fx3);
    if (fx4 != nullptr) fxs.push_back(fx4);
    if (fx5 != nullptr) fxs.push_back(fx5);
    if (fx6 != nullptr) fxs.push_back(fx6);
    if (fx7 != nullptr) fxs.push_back(fx7);
    if (fx8 != nullptr) fxs.push_back(fx8);
    if (fx9 != nullptr) fxs.push_back(fx9);
}

void Multiplex::flush() {
    for (Fx *fx : fxs) {
        fx->flush();
    }
}

void Multiplex::loop() {
    for (Fx *fx : fxs) {
        fx->loop();
    }
}

void Multiplex::reset() {
    for (Fx *fx : fxs) {
        fx->reset();
    }
}
