#include "Juggle.h"

Juggle::Juggle(Strip *strip) {
    this->strip = strip;
    for(uint8_t i = 0; i < dots; i++) {
        pixel[i].setup(strip);
    }
}

void Juggle::reset() {
    clear(strip);
    for(uint8_t i = 0; i < dots; i++) {
        pixel[i].reset();
    }
}

void Juggle::loop() {
    strip->fade(faderate);
    
    for(uint8_t i = 0; i < dots; i++) {
        pixel[i].set(beatsin16(basebeat + i, 0, strip->last()), CHSV(hue + i * hueIncrement, saturation, brightness));
    }
}
