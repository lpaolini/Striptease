#ifndef Interval_h
#define Interval_h

#include <Arduino.h>

class Interval {
    private:
        elapsedMicros timeMicroseconds = 0;

    public:
        void reset() {
            timeMicroseconds = 0;
        }

        double time(double interval) {
            double intervalMicroseconds = interval * 65536000;
            while (timeMicroseconds >= intervalMicroseconds) {
                timeMicroseconds -= intervalMicroseconds;
            }
            return double(timeMicroseconds) / double(intervalMicroseconds);
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
