#include "Spectrum.h"

Spectrum::Spectrum(Strip *strip, AudioChannel *audioChannel) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    reset();
}

void Spectrum::reset() {
    clear(strip);

    timer.reset();
}

void Spectrum::loop() {
    if (timer.isElapsed()) {
        strip->fade(10);
        for (uint8_t i = 0; i < 40; i++) {
            uint8_t brightness = audioChannel->fftBin[i] > .01 ? 255 : 10;
            (*(strip->leds))[i] = CHSV(0, 255, brightness);
        }
    }
}
