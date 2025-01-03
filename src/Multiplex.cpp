#include "Multiplex.h"

Multiplex::Multiplex(
    Fx *fx01, Fx *fx02, Fx *fx03, Fx *fx04, Fx *fx05, Fx *fx06, Fx *fx07, Fx *fx08, Fx *fx09, Fx *fx10,
    Fx *fx11, Fx *fx12, Fx *fx13, Fx *fx14, Fx *fx15, Fx *fx16, Fx *fx17, Fx *fx18, Fx *fx19, Fx *fx20
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
