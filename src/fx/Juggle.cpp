#include "Juggle.h"

Juggle::Juggle(Strip *strip, State *state) : Fx(strip, state) {
    for(uint8_t i = 0; i < DOTS; i++) {
        pixel[i].setup(strip);
    }
}

void Juggle::reset() {
    clear();
    for(uint8_t i = 0; i < DOTS; i++) {
        pixel[i].reset();
    }
    fadeTimer = 0;
}

void Juggle::loop() {
    if (fadeTimer >= 10) {
        fadeTimer -= 10;
        strip->fade(MIN_FADE_RATE + state->linearFxSpeed * (MAX_FADE_RATE - MIN_FADE_RATE));
    }
    
    for(uint8_t i = 0; i < DOTS; i++) {
        uint8_t beat = MIN_BEAT + state->linearFxSpeed * (MAX_BEAT - MIN_BEAT) + i;
        pixel[i].set(beatsin16(beat, 0, strip->last()), CHSV(i * HUE_INCREMENT, 255, 255));
    }
}
