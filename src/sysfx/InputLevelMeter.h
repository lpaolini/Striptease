#ifndef InputLevelMeter_h
#define InputLevelMeter_h

#include <Arduino.h>
#include "Fx.h"
#include "Strip.h"
#include "AudioChannel.h"
#include "AudioSensor.h"

class InputLevelMeter : public Fx {
    private:
        const static uint16_t CLIP_HOLD = 500;
        const static uint16_t BEAT_HOLD = 100;
        AudioSensor *audioSensor;
        elapsedMillis clipTimer;
        elapsedMillis beatTimer;

    public:
        InputLevelMeter(Strip *strip, AudioChannel *audioChannel, AudioSensor *audioSensor);
        void loop();
        void reset();
};

#endif
