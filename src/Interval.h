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

        float time(float interval) {
            float intervalMilliseconds = interval * 65536;
            while (timeMilliseconds >= intervalMilliseconds) {
                timeMilliseconds -= intervalMilliseconds;
            }
            return float(timeMilliseconds) / float(intervalMilliseconds);
        }

        static float toTriangle(float v) {
            return v < .5 ? 2 * v : 2 * (1 - v);
        }

        static float toSquare(float v, float duty) {
            return v < duty ? 1 : 0;
        }

        static float toWave(float v) {
            return (1 + sin(v * TWO_PI)) / 2;
        }
};

#endif
