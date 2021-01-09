#include "Fire.h"

Fire::Fire(Strip *strip, AudioChannel *audioChannel) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    // Array of temperature readings at each simulation cell
    heat = new uint8_t[strip->count];
    reset();
}

Fire::~Fire() {
    delete[] heat;
}

void Fire::reset() {
    clear(strip);
    if (random(2) == 0) {
        palette = HOT;
    } else {
        palette = COLD;
    }
    timer.reset();
}

void Fire::loop() {
    random16_add_entropy(random());

    if (timer.isElapsed()) {
        // Step 1.  Cool down every cell a little
        for(int i = 0; i < strip->count; i++) {
            heat[i] = qsub8(heat[i],  random8(0, ((COOLING * 10) / strip->count) + 2));
        }
    
        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for(int k = strip->count - 1; k >= 2; k--) {
            heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
        }
        
        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        bool trigger = audioChannel->signalDetected
            ? audioChannel->beatDetected || random8() < (3 + audioChannel->rms * 100)
            : random8() < SPARKING;

        if (trigger) {
            int y = random8(7);
            heat[y] = qadd8(heat[y], random8(160, 255));
        }

        // Step 4.  Map from heat cells to LED colors
        for( int j = 0; j < strip->count; j++) {
            // Scale the heat value from 0-255 down to 0-240
            // for best results with color palettes.
            byte colorindex = scale8(heat[j], 240);
            CRGB color = ColorFromPalette(palette, colorindex);
            int pixelnumber;
            if(reversed) {
                pixelnumber = (strip->count-1) - j;
            } else {
                pixelnumber = j;
            }
            (*(strip->leds))[pixelnumber] = color;
        }
    }
}
