#ifndef Easing_h
#define Easing_h

#include <Arduino.h>

class Easing {
    public:
        static double easeInOutSine(double x) {
            return -(cos(PI * x) - 1) / 2;
        }

        static double deltaEaseInOutSine(double x1, double x0) {
            return easeInOutSine(x1) - easeInOutSine(x0);
        }

        static double easeInOutCubic(double x) {
            return x < 0.5
                ? 4 * pow(x, 3)
                : 1 - pow(-2 * x + 2, 3) / 2;
        }

        static double deltaEaseInOutCubic(double x1, double x0) {
            return easeInOutCubic(x1) - easeInOutCubic(x0);
        }
};

#endif
