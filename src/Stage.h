#ifndef Stage_h
#define Stage_h

#include <Arduino.h>
#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#include <algorithm>

#include "Fx.h"
#include "Multiplex.h"
#include "strip/PhysicalStrip.h"
#include "strip/virtual/JoinedStrip.h"
#include "strip/virtual/ReversedStrip.h"
#include "strip/virtual/SubStrip.h"

// System fxs

#include "sysfx/CycleSpeed.h"
#include "sysfx/InputLevelMeter.h"
#include "sysfx/MicGainMeter.h"
#include "sysfx/SpeedMeter.h"

// Fxs

#include "fx/Ants.h"
#include "fx/Background.h"
#include "fx/Beat.h"
#include "fx/Blackout.h"
#include "fx/Blur.h"
#include "fx/Bounce.h"
#include "fx/Chaser.h"
#include "fx/ColorBar.h"
#include "fx/ColorTwinkles.h"
#include "fx/DeepSpace.h"
#include "fx/Drops.h"
#include "fx/Elastic.h"
#include "fx/Fire.h"
#include "fx/FastPulse.h"
#include "fx/Fireworks.h"
#include "fx/Glitter.h"
#include "fx/Jelly.h"
#include "fx/Juggle.h"
#include "fx/MarchingRainbow.h"
#include "fx/Matrix.h"
#include "fx/Motion.h"
#include "fx/Orbit.h"
#include "fx/PeakMeter.h"
#include "fx/Photons.h"
#include "fx/Rainbow.h"
#include "fx/RainbowMelt.h"
#include "fx/Ripple.h"
#include "fx/RippleReflections.h"
#include "fx/Scan.h"
#include "fx/Scroller.h"
#include "fx/Sinelon.h"
#include "fx/SineMeter.h"
#include "fx/Sparks.h"
#include "fx/Spectrum.h"
#include "fx/Spiral.h"
#include "fx/Strobe.h"
#include "fx/SubtleWave.h"
#include "fx/Traffic.h"
#include "fx/Vertigo.h"
#include "fx/Volcane.h"
#include "fx/VU1.h"
#include "fx/VU2.h"

class Stage {
    private:
        std::vector<Strip *> strips;
        std::vector<Fx *> fxs;
        std::vector<uint16_t> randomFxIndexes;
        uint16_t randomFxIndex = 0;
        Fx *cycleSpeed;
        Fx *speedMeter;
        Fx *micGainMeter;
        Fx *inputLevelMeter;

    protected:
        #if defined(ARDUINO_TEENSY40)
        const static uint8_t CH1_PIN = 14;
        const static uint8_t CH2_PIN = 17;
        const static uint8_t CH3_PIN = 1;
        #endif
        #if defined(ARDUINO_TEENSY41)
        const static uint8_t CH1_PIN = 17;
        const static uint8_t CH2_PIN = 14;
        const static uint8_t CH3_PIN = 35;
        const static uint8_t CH4_PIN = 1;
        const static uint8_t CH5_PIN = 24;
        const static uint8_t CH6_PIN = 29;
        #endif

        void addFx(
            Fx *fx01 = nullptr, 
            Fx *fx02 = nullptr, 
            Fx *fx03 = nullptr, 
            Fx *fx04 = nullptr, 
            Fx *fx05 = nullptr, 
            Fx *fx06 = nullptr, 
            Fx *fx07 = nullptr, 
            Fx *fx08 = nullptr, 
            Fx *fx09 = nullptr,
            Fx *fx10 = nullptr,
            Fx *fx11 = nullptr, 
            Fx *fx12 = nullptr, 
            Fx *fx13 = nullptr, 
            Fx *fx14 = nullptr, 
            Fx *fx15 = nullptr, 
            Fx *fx16 = nullptr, 
            Fx *fx17 = nullptr, 
            Fx *fx18 = nullptr, 
            Fx *fx19 = nullptr,
            Fx *fx20 = nullptr
        ) {
            clear();
            Fx *fx = new Multiplex(
                fx01, fx02, fx03, fx04, fx05, fx06, fx07, fx08, fx09, fx10,
                fx11, fx12, fx13, fx14, fx15, fx16, fx17, fx18, fx19, fx20
            );
            randomFxIndexes.push_back(fxs.size());
            fxs.push_back(fx);
        }

        template<uint16_t SIZE, uint8_t PIN, uint16_t DENSITY>
        Strip *addStrip() {
            Strip *strip = new PhysicalStrip<SIZE, PIN, DENSITY>();
            strips.push_back(strip);
            return strip;
        }

        void setCycleSpeedFx(Fx *fx1 = nullptr, Fx *fx2 = nullptr) {
            cycleSpeed = new Multiplex(fx1, fx2);
        }
        
        void setSpeedMeterFx(Fx *fx1 = nullptr, Fx *fx2 = nullptr) {
            speedMeter = new Multiplex(fx1, fx2);
        }
        
        void setMicGainMeterFx(Fx *fx1 = nullptr, Fx *fx2 = nullptr) {
            micGainMeter = new Multiplex(fx1, fx2);
        }
        
        void setInputLevelMeterFx(Fx *fx1 = nullptr, Fx *fx2 = nullptr) {
            inputLevelMeter = new Multiplex(fx1, fx2);
        }

    public:
        void clear() {
            for (Strip *strip : strips) {
                strip->off();
            }
        }
        
        void fade(uint8_t amount = 1) {
            for (Strip *strip : strips) {
                strip->fade(amount);
            }
        }
        
        void blur(uint8_t amount = 1) {
            for (Strip *strip : strips) {
                strip->blur(amount);
            }
        }
        
        uint16_t getFxCount() {
            return fxs.size();
        }
        
        uint16_t getNextFxIndex(uint16_t index) {
            return (index + 1) % getFxCount();
        }
        
        uint16_t getPrevFxIndex(uint16_t index) {
            return (index + getFxCount() - 1) % getFxCount();
        }
        
        uint16_t getRandomFxIndex() {
            if (randomFxIndex == 0) {
                std::random_shuffle(randomFxIndexes.begin(), randomFxIndexes.end());
            }
            randomFxIndex = (randomFxIndex + 1) % getFxCount();
            return randomFxIndexes[randomFxIndex];
        }
        
        Fx *getFx(uint16_t index) {
            return fxs[index];
        }
        
        Fx *getCycleSpeedFx() {
            return cycleSpeed;
        }
        
        Fx *getSpeedMeterFx() {
            return speedMeter;
        }
        
        Fx *getMicGainMeterFx() {
            return micGainMeter;
        }
        
        Fx *getInputLevelMeterFx() {
            return inputLevelMeter;
        }
};

#endif
