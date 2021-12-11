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
        double center;
        double radius;
        double angle;
        double angularSpeed;
        double eccentricity;
        double eccentricityAngle;
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
        EllipticMotion& setCenter(double center);
        EllipticMotion& setRadius(double radius);
        EllipticMotion& setAngle(double angle);
        EllipticMotion& setAngularSpeed(double angularSpeed);
        EllipticMotion& setEccentricity(double eccentricity);
        EllipticMotion& setEccentricityAngle(double eccentricityAngle);
        EllipticMotion& setOverwrite(bool overwrite);
        void loop();
};

#endif
