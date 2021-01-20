#ifndef Easing_h
#define Easing_h

#include <Arduino.h>

class Easing {
    public:
        static float easeInOutSine(float x) {
            return -(cos(PI * x) - 1) / 2;
        }

        static float deltaEaseInOutSine(float x1, float x0) {
            return easeInOutSine(x1) - easeInOutSine(x0);
        }

        static float easeInOutCubic(float x) {
            return x < 0.5
                ? 4 * pow(x, 3)
                : 1 - pow(-2 * x + 2, 3) / 2;
        }

        static float deltaEaseInOutCubic(float x1, float x0) {
            return easeInOutCubic(x1) - easeInOutCubic(x0);
        }
};

#endif
