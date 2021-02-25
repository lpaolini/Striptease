#ifndef EllipticMotion_h
#define EllipticMotion_h

#include <Arduino.h>
#include <FastLED.h>
#include "Strip.h"
#include "Pixel.h"
#include "State.h"

class EllipticMotion {
    private:
        static const uint8_t MIN_BRIGHTNESS = 75;
        Strip *strip;
        elapsedMicros timeElapsed;
        float center;
        float radius;
        float angle;
        float angularSpeed;
        float eccentricity;
        float eccentricityAngle;
        bool overwrite;
        Pixel pixel;

    public:
        uint8_t hue;
        uint8_t saturation;
        EllipticMotion();
        EllipticMotion& setup(Strip *strip);
        EllipticMotion& reset();
        EllipticMotion& setHue(uint8_t hue);
        EllipticMotion& setSaturation(uint8_t saturation);
        EllipticMotion& setCenter(float center);
        EllipticMotion& setRadius(float radius);
        EllipticMotion& setAngle(float angle);
        EllipticMotion& setAngularSpeed(float angularSpeed);
        EllipticMotion& setEccentricity(float eccentricity);
        EllipticMotion& setEccentricityAngle(float eccentricityAngle);
        EllipticMotion& setOverwrite(bool overwrite);
        void loop();
};

#endif
