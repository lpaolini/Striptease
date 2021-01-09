#include "Strobe.h"

Strobe::Strobe(Strip *strip, AudioChannel *audioChannel, State *state) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    this->state = state;
}

void Strobe::reset() {
    clear(strip);
    timer.reset();
}

void Strobe::loop() {
    if (timer.isElapsed()) {
        strip->fade(1);
        strip->leds->blur1d(100);
    }

    bool trigger = audioChannel->signalDetected
        ? audioChannel->beatDetected
        : !random(100);

    if (trigger) {
        strip->off();
        int count = random8(2, 5);
        CRGB color = ColorFromPalette(Strobe_PALETTE, state->fastRotatingHue);
        for (int i = 0; i < count; i++) {
            strip->paintRandomPos(SEGMENT_SIZE, color);
        }
    }
}
