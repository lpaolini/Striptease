#include "Strobe.h"

Strobe::Strobe(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    audioTrigger = new AudioTrigger(audioChannel);
}

Strobe::~Strobe() {
    delete audioTrigger;
}

void Strobe::reset() {
    clear();
    timer.reset();
    audioTrigger->reset();
}

void Strobe::loop() {
    bool trigger = audioTrigger->triggered(1);

    if (trigger) {
        strip->off();
        int count = random8(2, 5);
        CRGB color = ColorFromPalette(PALETTE, random8());
        for (int i = 0; i < count; i++) {
            strip->paintRandomPos(SEGMENT_SIZE, color, true);
        }
    }
}
