#include "Background.h"

Background::Background(Strip *strip, CRGB color) : Fx(strip) {
    this->color = color;
}

void Background::reset() {
    clear();
}

void Background::loop() {
    strip->paint(color);
}
