#include "Matrix.h"

Matrix::Matrix(Strip *strip, AudioChannel *audioChannel) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    up = new bool[strip->size()];
    down = new bool[strip->size()];
    for (int i = 0; i < strip->size() ; i++) {
        up[i] = down[i] = false;
    }
}

Matrix::~Matrix() {
    delete[] up;
    delete[] down;
}

void Matrix::reset() {
    clear(strip);
    downInterval.reset();
    upInterval.reset();
}

void Matrix::loop() {
    if (downInterval.isElapsed()) {
        down[strip->last()] = random8() < DOWN_PROBABILITY;
        for (int i = 0; i < strip->last(); i++) {
            down[i] = down[i + 1];
        }
        show();
    }

    trigger = trigger || audioChannel->trigger(UP_PROBABILITY);

    if (upInterval.isElapsed()) {
        up[0] = trigger;
        for (int i = strip->last(); i > 0; i--) {
            up[i] = up[i - 1];
        }
        show();
        trigger = false;
    }
}

void Matrix::show() {
    for (int i = 0; i < strip->size() ; i++) {
        strip->paint(i, (up[i] ? UP_COLOR : CRGB::Black) + (down[i] ? DOWN_COLOR : CRGB::Black), false);
    }
}
