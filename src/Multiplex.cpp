#include "Multiplex.h"

Multiplex::Multiplex(Fx *fx1, Fx *fx2, Fx *fx3, Fx *fx4, Fx *fx5, Fx *fx6) {
    this->fx1 = fx1;
    this->fx2 = fx2;
    this->fx3 = fx3;
    this->fx4 = fx4;
    this->fx5 = fx5;
    this->fx6 = fx6;
}

void Multiplex::flush() {
    if (fx1 != nullptr) fx1->flush();
    if (fx2 != nullptr) fx2->flush();
    if (fx3 != nullptr) fx3->flush();
    if (fx4 != nullptr) fx4->flush();
    if (fx5 != nullptr) fx5->flush();
    if (fx6 != nullptr) fx6->flush();
}

void Multiplex::loop() {
    if (fx1 != nullptr) fx1->loop();
    if (fx2 != nullptr) fx2->loop();
    if (fx3 != nullptr) fx3->loop();
    if (fx4 != nullptr) fx4->loop();
    if (fx5 != nullptr) fx5->loop();
    if (fx6 != nullptr) fx6->loop();
}

void Multiplex::reset() {
    if (fx1 != nullptr) fx1->reset();
    if (fx2 != nullptr) fx2->reset();
    if (fx3 != nullptr) fx3->reset();
    if (fx4 != nullptr) fx4->reset();
    if (fx5 != nullptr) fx5->reset();
    if (fx6 != nullptr) fx6->reset();
}
