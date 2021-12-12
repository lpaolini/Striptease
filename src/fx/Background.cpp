#include "Background.h"

Background::Background(Strip *strip, CRGB color) : Fx(strip) {
    this->color = color;
}

void Background::loop() {
    strip->paint(color);
}
