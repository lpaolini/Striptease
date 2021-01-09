#ifndef Fire_h
#define Fire_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "Fx.h"
#include "Timer.h"

class Fire : public Fx {
    private:
        const int SPARKING = 50;
        const int COOLING = 55;
        const CRGBPalette16 HOT = CRGBPalette16(CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
        const CRGBPalette16 COLD = CRGBPalette16(CRGB::Black, CRGB::Blue, CRGB::Aqua, CRGB::White);
        Strip *strip;
        AudioChannel *audioChannel;
        uint8_t *heat;
        CRGBPalette16 palette;
        bool reversed = false;
        Timer timer = Timer(10);

    public:
        Fire(Strip *strip, AudioChannel *audioChannel);
        ~Fire();
        void loop();
        void reset();
};

#endif
