#include "Blackout.h"

Blackout::Blackout(Strip *strip) {
    this->strip = strip;
}

void Blackout::reset() {
    clear(strip);
}

void Blackout::loop() {}
