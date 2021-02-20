#ifndef Fx_h
#define Fx_h

#include <Arduino.h>
#include "AudioChannel.h"
#include "State.h"
#include "Strip.h"

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

        void flush() {
            if (strip != nullptr) {
                strip->flush();
            }
        }

        void loopFlush() {
            loop();
            flush();
        }

        virtual void reset();
        virtual void loop();
};

#endif
