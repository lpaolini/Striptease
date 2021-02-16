#include "Blackout.h"

Blackout::Blackout(Strip *strip) : Fx(strip) {}

void Blackout::reset() {
    clear();
}

void Blackout::loop() {}
