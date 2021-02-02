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
        strip->blur(100);
    }

    bool trigger = audioChannel->trigger(5);

    if (trigger) {
        strip->off();
        int count = random8(2, 5);
        CRGB color = ColorFromPalette(PALETTE, state->fastRotatingHue);
        for (int i = 0; i < count; i++) {
            strip->paintRandomPos(SEGMENT_SIZE, color);
        }
    }
}
