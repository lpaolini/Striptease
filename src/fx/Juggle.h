#ifndef Juggle_h
#define Juggle_h

#include <Arduino.h>
#include <FastLED.h>
#include "Fx.h"
#include "Pixel.h"

class Juggle : public Fx {
    private:
        static const uint8_t DOTS = 5;
        Strip *strip;
        Pixel pixel[DOTS];
        
        uint8_t dots = DOTS ;
        uint8_t hueIncrement = 40;

        uint8_t hue = 0;
        uint8_t saturation = 255;
        uint8_t brightness = 255; 

        uint8_t basebeat = 10;
        uint8_t faderate = 2; 

    public:
        Juggle(Strip *strip);
        void loop();
        void reset();
};

#endif
