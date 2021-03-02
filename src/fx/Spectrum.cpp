#include "Spectrum.h"

Spectrum::Spectrum(Strip *strip, AudioChannel *audioChannel) : Fx(strip, audioChannel) {
    segmentSize = floor(strip->size() / 16);
}

void Spectrum::reset() {
    clear();
}

void Spectrum::loop() {
    strip->fade(20);
    for (int i = 0; i < 16; i++) {
        CRGB color = audioChannel->bands[i].peakDetected ? CRGB::Red : CRGB::Black;
        strip->paint(i * segmentSize + 1, (i + 1) * segmentSize - 2, color);
    }
}
