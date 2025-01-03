#include "BufferedStrip.h"

BufferedStrip::BufferedStrip(Strip *strip, double opacity) {
    this->strip = strip;
    this->opacity = max(0L, min(1L, opacity));
    this->leds = new CRGBSet(new CRGB[strip->size()], strip->size());
    setLeds(leds);
}

void BufferedStrip::flush() {
    for (uint16_t i = 0; i < strip->size(); i++) {
        strip->paint(i, (*leds)[i].scale8((uint8_t)(255 * opacity)), true);
    }
}
