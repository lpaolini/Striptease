#include "Spectrum.h"

Spectrum::Spectrum(Strip *strip, AudioChannel *audioChannel) : Fx(strip, audioChannel) {
    reset();
}

void Spectrum::reset() {
    clear();
}

void Spectrum::loop() {
    strip->fade(10);
    for (uint8_t i = 0; i < 40; i++) {
        uint8_t brightness = audioChannel->fftBin[i] > .01 ? 255 : 10;
        strip->paint(i, CHSV(0, 255, brightness), false);
    }
}
