#ifndef DeepSpace_h
#define DeepSpace_h

#include <Arduino.h>
#include <math.h>
#include "audio/AudioTrigger.h"
#include "Easing.h"
#include "Fx.h"
#include "Pixel.h"
#include "Point.h"
#include "Timer.h"

class DeepSpace : public Fx {
    private:
        enum Type {HIDDEN, NORMAL, HIGHLIGHT};
        struct Item {
            Point point;
            Pixel pixel;
            Type type;
        };
        static const uint16_t ITEMS = 250;
        static const uint16_t SPEED = 500;
        static constexpr double MIN_DISTANCE = 500;
        static constexpr double MAX_DISTANCE = 2000;
        static constexpr double MAX_MUTATION_DISTANCE = 500;
        static constexpr double MAX_SQUARED_DISTANCE = pow(MAX_DISTANCE, 2);
        static constexpr double MIN_STEERING = 30;
        static constexpr double MAX_STEERING = 120;
        static constexpr double MIN_TRANSITION_SPEED = 100;
        static constexpr double MAX_TRANSITION_SPEED = 300;
        CRGB baseColor, accentColor;
        AudioTrigger *audioTrigger;
        Item items[ITEMS];
        elapsedMicros time;
        double steeringAngle = 0;
        double transitionSpeed = 0;
        double transition = 1;
        Timer timer = Timer(1000);
        void loopItem(Item &item, double translationY, double rotation, bool &trigger);
        void randomizeItem(Item &item);

    public:
        DeepSpace(Strip *strip, AudioChannel *audioChannel, State *state, CRGB baseColor = CRGB::Blue, CRGB accenttColor = CRGB::Red);
        ~DeepSpace();
        void loop();
        void reset();
};

#endif
