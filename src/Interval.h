#ifndef Interval_h
#define Interval_h

#include <Arduino.h>

class Interval {
    private:
        elapsedMillis timeMilliseconds = 0;

    public:
        void reset() {
            timeMilliseconds = 0;
        }

        double time(double interval) {
            double intervalMilliseconds = interval * 65536;
            while (timeMilliseconds >= intervalMilliseconds) {
                timeMilliseconds -= intervalMilliseconds;
            }
            return double(timeMilliseconds) / double(intervalMilliseconds);
        }

        static double frac(double v) {
            double whole;
            double fractional = modf(v, &whole);
            return fractional < 0 ? 1 - fractional : fractional;
        }

        static double toTriangle(double v) {
            double v0 = frac(v);
            return v0 < .5 ? 2 * v0 : 2 * (1 - v0);
        }

        static double toSquare(double v, double duty) {
            double v0 = frac(v);
            return v0 < duty ? 1 : 0;
        }

        static double toWave(double v) {
            double v0 = frac(v);
            return (1 + sin(v0 * TWO_PI)) / 2;
        }
};

#endif
