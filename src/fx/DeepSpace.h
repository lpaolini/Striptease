#ifndef DeepSpace_h
#define DeepSpace_h

#include <Arduino.h>
#include <math.h>
#include "AudioChannel.h"
#include "AudioTrigger.h"
#include "Easing.h"
#include "Fx.h"
#include "Pixel.h"
#include "Point.h"
#include "Strip.h"
#include "State.h"
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
        static constexpr float MIN_DISTANCE = 500;
        static constexpr float MAX_DISTANCE = 2000;
        static constexpr float MAX_MUTATION_DISTANCE = 500;
        static constexpr float MAX_SQUARED_DISTANCE = pow(MAX_DISTANCE, 2);
        static constexpr float MIN_STEERING = 30;
        static constexpr float MAX_STEERING = 150;
        static constexpr float MIN_TRANSITION_SPEED = 100;
        static constexpr float MAX_TRANSITION_SPEED = 500;
        AudioTrigger *audioTrigger;
        Item items[ITEMS];
        elapsedMicros time;
        float steeringAngle = 0;
        float transitionSpeed = 0;
        float transition = 1;
        Timer timer = Timer(1000);
        void loopItem(Item &item, float translationY, float rotation, bool &trigger);
        void randomizeItem(Item &item);

    public:
        DeepSpace(Strip *strip, AudioChannel *audioChannel, State *state);
        ~DeepSpace();
        void loop();
        void reset();
};

#endif
