#ifndef MicGainMeter_h
#define MicGainMeter_h

#include <Arduino.h>
#include "Fx.h"
#include "Strip.h"
#include "AudioChannel.h"
#include "AudioSensor.h"

class MicGainMeter : public Fx {
    private:
        const static uint16_t CLIP_HOLD = 500;
        const static uint16_t BEAT_HOLD = 100;
        AudioSensor *audioSensor;
        elapsedMillis clipTimer;
        elapsedMillis beatTimer;

    public:
        MicGainMeter(Strip *strip, AudioChannel *audioChannel, AudioSensor *audioSensor);
        void loop();
        void reset();
};

#endif
