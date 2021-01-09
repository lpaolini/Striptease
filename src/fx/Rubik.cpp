#include "Rubik.h"

Rubik::Rubik(Strip *strip) {
    this->strip = strip;
    reset();
}

void Rubik::reset() {
    clear(strip);
    randomize();
    timer.reset();
}

void Rubik::randomize() {
    for (int i = 0; i < 3; i++) {
        currentColors[i + 3] = currentColors[i];
        currentColors[i] = colors[random8(6)];
    }
}

void Rubik::loop() {
    if (timer.isElapsed()) {
        strip->leds->fadeToBlackBy(50);

        angle += step;
        if (angle > 16383) {
            angle = 0;
            randomize();
        }
    
        long pl = cos16(angle + 24576);
        long pc = cos16(angle + 40760);
        long pr = cos16(angle + 57344);
    
        int dl = (pc - pl) / 3;
        int dr = (pr - pc) / 3;
        uint8_t bl = uint8_t(sin16(angle) / 128);
        uint8_t br = uint8_t(cos16(angle) / 128);

        currentColors[0].val = bl;
        currentColors[1].val = bl;
        currentColors[2].val = bl;
        currentColors[3].val = br;
        currentColors[4].val = br;
        currentColors[5].val = br;
        
        facet(pl, dl, 0, currentColors[0]);
        facet(pl, dl, 1, currentColors[1]);
        facet(pl, dl, 2, currentColors[2]);
        facet(pc, dr, 0, currentColors[3]);
        facet(pc, dr, 1, currentColors[4]);
        facet(pc, dr, 2, currentColors[5]);
    }
}

void Rubik::facet(long start, int len, int index, CRGB color) {
    paint(start + len * index, len, color);
}

void Rubik::paint(long start, int len, CRGB color) {
    int nFrom = map(start, -32768, 32767, 0, strip->count - 1);
    int nTo = map(start + len, -32768, 32767, 0, strip->count - 1);
    int posFrom = min(nFrom, nTo);
    int posTo = max(nFrom, nTo);
    (*(strip->leds))(posFrom, posTo) = color;
}
