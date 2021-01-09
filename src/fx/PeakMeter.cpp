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
    CRGB color = beat < 100 ? CRGB::Aqua : CRGB::Blue;
    (*(strip->leds))(0, peakSmooth * (strip->count - 1)) = color;
    (*(strip->leds))(peakHold * (strip->count - 1), strip->count - 1) = CRGB::DarkRed;
}
