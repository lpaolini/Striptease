#ifndef Fx_h
#define Fx_h

#include "audio/AudioChannel.h"
#include "State.h"
#include "strip/Strip.h"

class Fx {
    protected:
        Strip *strip;
        AudioChannel *audioChannel;
        State *state;

    public:
        Fx() {};

        Fx(Strip *strip) {
            this->strip = strip;
        };

        Fx(Strip *strip, AudioChannel *audioChannel) {
            this->strip = strip;
            this->audioChannel = audioChannel;
        };

        Fx(Strip *strip, AudioChannel *audioChannel, State *state) {
            this->strip = strip;
            this->audioChannel = audioChannel;
            this->state = state;
        };

        Fx(Strip *strip, State *state) {
            this->strip = strip;
            this->state = state;
        };

        void clear() {
            if (strip != nullptr) {
                strip->off();
            }
        }

        virtual void flush() {
            if (strip != nullptr) {
                strip->flush();
            }
        }

        void loopFlush() {
            loop();
            flush();
        }

        // virtual void reset();
        virtual void reset() {
            clear();
        }

        virtual void loop() {
            strip->off();
            beforeRender();
            for (int16_t index = strip->first(); index < strip->last(); index++) {
                double x = double(index) / strip->last();                
                strip->paint(index, render(index, x));
            }
        }
        
        virtual void beforeRender() {
            return;
        }

        virtual CRGB render(int16_t index, double x) {
            return CRGB::Black;
        }

        static double frac(double v) {
            double whole;
            double fractional = modf(v, &whole);
            return fractional < 0 ? 1 - fractional : fractional;
        }

        static double triangle(double v) {
            double v0 = frac(v);
            return v0 < .5 ? 2 * v0 : 2 * (1 - v0);
        }

        static double square(double v, double duty) {
            double v0 = frac(v);
            return v0 < duty ? 1 : 0;
        }

        static double wave(double v) {
            double v0 = frac(v);
            return (1 + sin(v0 * TWO_PI)) / 2;
        }

        static CRGB hsv(double h, double s, double v) {
            return CHSV(255 * h, 255 * s, 255 * v);
        }

        static CRGB rgb(double r, double g, double b) {
            return CRGB(255 * r, 255 * g, 255 * b);
        }
};

#endif
