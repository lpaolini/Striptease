#ifndef Fire_h
#define Fire_h

#include <Arduino.h>
#include <FastLED.h>
#include "AudioSensor.h"
#include "Fx.h"
#include "Timer.h"

class Fire : public Fx {
    private:
        static const int SPARKING = 5;
        static const int COOLING = 55;
        const CRGBPalette16 HOT = CRGBPalette16(HeatColors_p);
        const CRGBPalette16 COLD = CRGBPalette16(CRGB::Black, CRGB::Blue, CRGB::Aqua, CRGB::White);
        Strip *strip;
        AudioChannel *audioChannel;
        uint8_t *heat;
        CRGBPalette16 palette;
        Timer timer = Timer(5);

    public:
        Fire(Strip *strip, AudioChannel *audioChannel);
        ~Fire();
        void loop();
        void reset();
};

#endif
