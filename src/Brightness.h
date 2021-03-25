#ifndef Brightness_h
#define Brightness_h

#include <Arduino.h>
#include <FastLED.h>

class Brightness {
    private:
        static const uint8_t BRIGHTNESS_STEPS = 40;
        static const uint8_t MIN_BRIGHTNESS = 20;
        static const uint8_t INITIAL_BRIGHTNESS = 10;
        static const uint16_t ON_DURATION_MS = 50;
        static const uint16_t OFF_DURATION_MS = 150;
        uint8_t brightness = INITIAL_BRIGHTNESS;
        uint8_t count = 0;
        bool on = false;
        elapsedMillis timer;
        void applyBrightness(bool dim = false);
        void dim(bool on);

    public:
        void init();
        void set(uint8_t brightness);
        void increase();
        void decrease();
        void blink(uint8_t count);
        void loop();
};

#endif
