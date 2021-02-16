#include "ColorBar.h"

ColorBar::ColorBar(Strip *strip, State *state) : Fx(strip, state) {}

void ColorBar::reset() {
    clear();
}

void ColorBar::loop() {
    strip->paint(CHSV(255 * state->linearFxSpeed, 255, 128));
}
