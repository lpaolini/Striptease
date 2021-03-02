#ifndef State_h
#define State_h

#include <FastLED.h>

class State {
    private:
        static const uint8_t DEFAULT_FX_SPEED = 20;
        static const uint8_t DEFAULT_CYCLE_SPEED = 50;
        elapsedMicros microseconds;
        float rotatingHueInternal;
        uint8_t fxSpeed;
        uint8_t cycleSpeed;

    public:
        float linearFxSpeed;
        float parabolicFxSpeed;
        float linearCycleSpeed;
        uint8_t rotatingHue;
        State();
        void setup();
        void setFxSpeed(uint8_t speed);
        uint8_t getFxSpeed();
        void decreaseFxSpeed();
        void increaseFxSpeed();
        void setCycleSpeed(uint8_t speed);
        uint8_t getCycleSpeed();
        void decreaseCycleSpeed();
        void increaseCycleSpeed();
        void loop();
};

#endif
