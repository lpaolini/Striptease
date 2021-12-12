#include "PeakMeter.h"

PeakMeter::PeakMeter(Strip *strip, AudioChannel *audioChannel) : Fx(strip, audioChannel) {
    pixel.setup(strip);
    reset();
}

void PeakMeter::reset() {
    clear();
    pixel.reset();
}

void PeakMeter::loop() {
    strip->off();
    double peakSmooth = audioChannel->peakSmooth;
    double peakHold = audioChannel->peakHold;
    if (audioChannel->beatDetected) {
        beat = 0;
    }
    strip->paintNormalized(0, peakSmooth, CRGB::Blue, false);
    if (beat < 100) {
        strip->paintNormalizedSize(0, 5, CRGB::Aqua, false);
    }
    strip->paintNormalized(peakHold, 1, CRGB::DarkRed, false);
}
