#include "Fire.h"

Fire::Fire(Strip *strip, AudioChannel *audioChannel) : Fx(strip, audioChannel) {
    audioTrigger = new AudioTrigger(audioChannel);
    // Array of temperature readings at each simulation cell
    heat = new uint8_t[strip->size()];
    reset();
}

Fire::~Fire() {
    delete audioTrigger;
    delete[] heat;
}

void Fire::reset() {
    clear();
    if (random8(2) == 0) {
        palette = HOT;
    } else {
        palette = COLD;
    }
}

void Fire::loop() {
    // Step 1.  Cool down every cell a little
    for (uint16_t i = 0; i < strip->size(); i++) {
        heat[i] = qsub8(heat[i],  random8(0, COOLING * 10 / strip->size() + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (uint16_t i = strip->last(); i >= 2; i--) {
        heat[i] = (heat[i - 1] + 2 * heat[i - 2]) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if (audioTrigger->triggered(SPARKING, 3 + audioChannel->rms * 10)) {
        int y = random8(7);
        heat[y] = qadd8(heat[y], random8(160, 255));
    }

    // Step 4.  Map from heat cells to LED colors
    for (uint16_t i = 0; i < strip->size(); i++) {
        // Scale the heat value from 0-255 down to 0-240 for best results with color palettes
        uint8_t colorindex = scale8(heat[i], 240);
        CRGB color = ColorFromPalette(palette, colorindex);
        strip->paint(i, color, false);
    }
}
