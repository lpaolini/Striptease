#ifndef DeepSpace_h
#define DeepSpace_h

#include <Arduino.h>
#include <math.h>
#include "AudioChannel.h"
#include "Fx.h"
#include "Pixel.h"
#include "Strip.h"
#include "State.h"
#include "Timer.h"

class DeepSpace : public Fx {
    private:
        const CRGBPalette16 PALETTE = CRGBPalette16(CRGB::Blue, CRGB::Red);
        enum Type {HIDDEN, BLUE, RED};
        struct Item {
            float x;
            float y;
            uint8_t hue;
            Pixel pixel;
            bool visible;
            Type type;
            // bool visible;
        };
        Strip *strip;
        AudioChannel *audioChannel;
        State *state;
        static const uint8_t ITEMS = 100;
        static const uint16_t MIN_X_DISTANCE = 10;
        static const uint16_t MAX_X_DISTANCE = 1000;
        static const uint16_t MIN_Y_DISTANCE = 1000;
        static const uint16_t MAX_Y_DISTANCE = 2000;
        static const uint16_t MAX_MUTATION_X_DISTANCE = 500;
        static const uint16_t MAX_MUTATION_Y_DISTANCE = 500;
        static constexpr float MAX_SQUARE_DISTANCE = powf(MAX_X_DISTANCE, 2) + powf(MAX_Y_DISTANCE, 2);
        static const uint16_t SPEED = 500;
        Item items[ITEMS];
        elapsedMicros time;
        float v = -SPEED;
        void loopItem(Item &item, float dT, bool &trigger);
        void randomizeItem(Item &item);

    public:
        DeepSpace(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
