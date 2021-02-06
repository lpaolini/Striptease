#include "ColorBar.h"

ColorBar::ColorBar(Strip *strip, State *state) {
    this->strip = strip;
    this->state = state;
}

void ColorBar::reset() {
    clear(strip);
}

void ColorBar::loop() {
    strip->paint(CHSV(255 * state->linearFxSpeed, 255, 128));
}
