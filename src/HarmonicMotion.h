#ifndef HarmonicMotion_h
#define HarmonicMotion_h

#include <Arduino.h>
#include <FastLED.h>
#include "Strip.h"

class HarmonicMotion {
    private:
        struct Limit {
            float x;
            float r = 1;
            int8_t boundTrigger = 0;
        };
        Strip *strip;
        elapsedMicros timeElapsed;
        float a0 = 0;            // first order acceleration
        float a1 = 0;            // second order acceleration
        float a2 = 0;            // third order acceleration
        float k = 0;             // elastic constant
        float b = 0;             // dampening
        float x = 0;             // position
        float x0 = 0;            // fixed point position
        float v = 0;             // velocity
        int start = 0;           // start led
        int end = 0;             // end led
        bool mirror;             // mirror
        bool fill;               // fill
        bool showWhenStable;     // show when stable
        bool overwrite;          // add to pixel color
        float xPrev;             // previous position
        float vPrev;             // previous velocity
        Limit lowerLimit;        // lower limit
        Limit upperLimit;        // upper limit
        int getLowerLimitCompensation();
        int getUpperLimitCompensation();
        bool isLowerLimit();
        bool isUpperLimit();
        void update();
        void show(float x, float xPrev, bool mirror);
        
    public:
        CRGB color;
        HarmonicMotion();
        HarmonicMotion& setup(Strip *strip);
        HarmonicMotion& reset();
        HarmonicMotion& setColor(CRGB color = CRGB::White);
        HarmonicMotion& setAcceleration(float a0, float a1 = 0, float a2 = 0);
        HarmonicMotion& setElasticConstant(float k);
        HarmonicMotion& setDamping(float b);
        HarmonicMotion& setCriticalDamping();
        HarmonicMotion& setPosition(float x);
        HarmonicMotion& setRandomPosition();
        HarmonicMotion& setVelocity(float v);
        HarmonicMotion& setFixedPointPosition(float x0);
        HarmonicMotion& setRandomFixedPointPosition();
        HarmonicMotion& setUpperBound(float x, float r = 0, int8_t boundTrigger = 0);
        HarmonicMotion& setLowerBound(float x, float r = 0, int8_t boundTrigger = 0);
        HarmonicMotion& setRange(int start, int end);
        HarmonicMotion& setMirror(bool mirror);
        HarmonicMotion& setFill(bool fill);
        HarmonicMotion& setShowWhenStable(bool showWhenStable);
        HarmonicMotion& setOverwrite(bool overwrite);
        float getPosition();
        float getVelocity();
        float getFixedPointPosition();
        bool isStable();
        void loop();
};

#endif
