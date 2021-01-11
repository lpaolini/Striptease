#include "PeakMeter.h"

PeakMeter::PeakMeter(Strip *strip, AudioChannel *audioChannel) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    pixel.setup(strip);
    reset();
}

void PeakMeter::reset() {
    clear(strip);
    pixel.reset();
}

void PeakMeter::loop() {
    strip->off();
    float peakSmooth = audioChannel->peakSmooth;
    float peakHold = audioChannel->peakHold;
    if (audioChannel->beatDetected) {
        beat = 0;
    }
    strip->paintNormalized(0, peakSmooth, beat < 100 ? CRGB::Aqua : CRGB::Blue, false);
    strip->paintNormalized(peakHold, 1, CRGB::DarkRed, false);
}
