#include "MicGainMeter.h"

MicGainMeter::MicGainMeter(Strip *strip, AudioChannel *audioChannel, AudioSensor *audioSensor) : Fx(strip, audioChannel) {
    this->audioSensor = audioSensor;
}

void MicGainMeter::reset() {
    clear();
}

void MicGainMeter::loop() {
    strip->off();
    strip->paintNormalized(0, 1, CHSV(128, 255, 75), false);
    strip->paintNormalized(0, audioSensor->getNormalizedMicGain(), CHSV(128, 255, 255), false);
    if (audioChannel->clipping) {
        clipTimer = 0;
    }
    if (audioChannel->beatDetected) {
        beatTimer = 0;
    }
    CRGB color = clipTimer < CLIP_HOLD
        ? CRGB::Red 
        : beatTimer < BEAT_HOLD
            ? CRGB::Cyan
            : CRGB::White;
    strip->paintNormalizedSize(audioChannel->peakSmooth, 2, CRGB::White);
    strip->paintNormalizedSize(audioChannel->peakHold, 4, color, false);
}
