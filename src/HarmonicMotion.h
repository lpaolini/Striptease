#ifndef HarmonicMotion_h
#define HarmonicMotion_h

#include "strip/Strip.h"

class HarmonicMotion {
    public:
        enum ReboundMode {INSIDE = -1, OUTSIDE = 1, DEFAULT = 0};

    private:
        struct Limit {
            double x;
            double r = 1;
            ReboundMode reboundMode = DEFAULT;
        };
        Strip *strip;
        elapsedMicros timeElapsed;
        double a0 = 0;            // first order acceleration
        double a1 = 0;            // second order acceleration
        double a2 = 0;            // third order acceleration
        double k = 0;             // elastic constant
        double b = 0;             // dampening
        double x = 0;             // position
        double x0 = 0;            // fixed point position
        double v = 0;             // velocity
        int start = 0;            // start led
        int end = 0;              // end led
        bool mirror;              // mirror
        bool fill;                // fill
        bool showWhenStable;      // show when stable
        bool overwrite;           // add to pixel color
        double xPrev;             // previous position
        double vPrev;             // previous velocity
        Limit lowerLimit;         // lower limit
        Limit upperLimit;         // upper limit
        int getLowerLimitCompensation();
        int getUpperLimitCompensation();
        bool isLowerLimit();
        bool isUpperLimit();
        void update();
        void show(bool mirror);
        
    public:
        CRGB color;
        HarmonicMotion();
        HarmonicMotion& setup(Strip *strip);
        HarmonicMotion& reset();
        HarmonicMotion& setColor(CRGB color);
        HarmonicMotion& setAcceleration(double a0, double a1 = 0, double a2 = 0);
        HarmonicMotion& setElasticConstant(double k);
        HarmonicMotion& setDamping(double b);
        HarmonicMotion& setCriticalDamping(double correctionFactor = 1);
        HarmonicMotion& setPosition(double x);
        HarmonicMotion& setRandomPosition();
        HarmonicMotion& setVelocity(double v);
        HarmonicMotion& setFixedPointPosition(double x0);
        HarmonicMotion& setRandomFixedPointPosition();
        HarmonicMotion& setUpperBound(double x, double r = 0, ReboundMode mode = DEFAULT);
        HarmonicMotion& setLowerBound(double x, double r = 0, ReboundMode mode = DEFAULT);
        HarmonicMotion& setRange(int start, int end);
        HarmonicMotion& setMirror(bool mirror);
        HarmonicMotion& setFill(bool fill);
        HarmonicMotion& setShowWhenStable(bool showWhenStable);
        HarmonicMotion& setOverwrite(bool overwrite);
        double getFixedPointPosition();
        double getPosition();
        double getVelocity();
        double getAcceleration();
        bool isStable();
        void loop();
};

#endif
