#include "Brightness.h"

void Brightness::applyBrightness(bool dim) {
    double correctedBrightness = MIN_BRIGHTNESS + (255 - MIN_BRIGHTNESS) * pow(double(brightness) / (BRIGHTNESS_STEPS - 1), 2);
    FastLED.setBrightness(dim ? correctedBrightness / 2 : correctedBrightness);
}

void Brightness::dim(bool on) {
    this->on = on;
    applyBrightness(on);
    timer = 0;
}

void Brightness::init() {
    applyBrightness();
}

void Brightness::set(uint8_t brightness) {
    this->brightness = brightness;
    applyBrightness();
    Serial.print("Brightness set to ");
    Serial.println(brightness);
}

void Brightness::increase() {
    set(min(brightness + 1, BRIGHTNESS_STEPS - 1));
}

void Brightness::decrease() {
    set(max(brightness - 1, 0));
}

void Brightness::blink(uint8_t count) {
    this->count = count;
    dim(true);
}

void Brightness::loop() {
    if (count) {
        if (on) {
            if (timer > ON_DURATION_MS) {
                dim(false);
            }
        } else {
            if (timer > OFF_DURATION_MS) {
                if (--count) {
                    dim(true);
                }
            }
        }
    }
}
