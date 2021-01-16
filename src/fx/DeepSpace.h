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
        enum Type {HIDDEN, BLUE, PULSE, RED};
        struct Item {
            float x;
            float y;
            Pixel pixel;
            Type type;
        };
        Strip *strip;
        AudioChannel *audioChannel;
        State *state;
        static const uint16_t ITEMS = 250;
        static const uint16_t SPEED = 500;
        static constexpr float MIN_DISTANCE = 500;
        static constexpr float MAX_DISTANCE = 2000;
        static constexpr float MAX_MUTATION_DISTANCE = 500;
        static constexpr float MAX_SQUARE_DISTANCE = pow(MAX_DISTANCE, 2);
        static constexpr float MIN_STEERING = 30;
        static constexpr float MAX_STEERING = 150;
        Item items[ITEMS];
        elapsedMicros time;
        float speed = SPEED;
        float steeringAngle = 0;
        float transitionSpeed = 0;
        float transition = 1;
        Timer timer = Timer(1000);
        void loopItem(Item &item, float dT, bool &trigger);
        float deltaEaseInOutSine(float x1, float x0);
        void rotateItem(Item &item, float angle);
        void moveItem(Item &item, float distance);
        void randomizeItem(Item &item);

    public:
        DeepSpace(Strip *strip, AudioChannel *audioChannel, State *state);
        void loop();
        void reset();
};

#endif
