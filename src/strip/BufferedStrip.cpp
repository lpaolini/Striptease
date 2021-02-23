#include "BufferedStrip.h"

BufferedStrip::BufferedStrip(Strip *strip) {
    this->strip = strip;
    this->leds = new CRGBSet(new CRGB[strip->size()], strip->size());
    setLeds(leds);
}

void BufferedStrip::flush() {
    for (uint16_t i = 0; i < strip->size(); i++) {
        strip->paint(i, (*leds)[i], true);
    }
}
