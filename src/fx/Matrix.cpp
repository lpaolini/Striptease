#include "Matrix.h"

Matrix::Matrix(Strip *strip, AudioChannel *audioChannel, State *state) : Fx(strip, audioChannel, state) {
    audioTrigger = new AudioTrigger(audioChannel);
    up = new bool[strip->size()];
    down = new bool[strip->size()];
    for (uint16_t i = 0; i < strip->size() ; i++) {
        up[i] = down[i] = false;
    }
}

Matrix::~Matrix() {
    delete audioTrigger;
    delete[] up;
    delete[] down;
}

void Matrix::reset() {
    clear();
    countDown = DOWN_PERIOD;
    countUp = UP_PERIOD;

    for (uint16_t i = 0; i < strip->last(); i++) {
        up[i] = down[i] = false;
    }

    audioTrigger->reset();
}

void Matrix::loop() {
    audioTrigger->loop();
    addFromTop();
    addFromBottom();
    show();
}

void Matrix::addFromTop() {
    if (--countDown == 0) {
        // down[strip->last()] = !down[strip->last() - 1] && random8() < DOWN_PROBABILITY;
        down[strip->last()] = !down[strip->last() - 1] && random8() < 100 * state->parabolicFxSpeed;
        for (int i = 0; i < strip->last(); i++) {
            down[i] = down[i + 1];
        }
        countDown = DOWN_PERIOD;
    }
}

void Matrix::addFromBottom() {
    if (--countUp == 0) {
        up[0] = audioTrigger->triggered(.5);
        for (int i = strip->last(); i > 0; i--) {
            up[i] = up[i - 1];
        }
        countUp = UP_PERIOD;
    }
}

void Matrix::show() {
    for (int i = 0; i < strip->size() ; i++) {
        strip->paint(i, (up[i] ? UP_COLOR : CRGB::Black) + (down[i] ? DOWN_COLOR : CRGB::Black), false);
    }
}
