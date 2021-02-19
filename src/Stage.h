#ifndef Stage_h
#define Stage_h

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#include <vector>
#include <algorithm>

#include "Fx.h"
#include "Multiplex.h"
#include "PhysicalStrip.h"

// System fxs

#include "sysfx/CycleSpeed.h"
#include "sysfx/InputLevelMeter.h"
#include "sysfx/MicGainMeter.h"
#include "sysfx/SpeedMeter.h"

// Fxs

#include "fx/Ants.h"
#include "fx/Beat.h"
#include "fx/Bounce.h"
#include "fx/VU1.h"
#include "fx/VU2.h"
#include "fx/Elastic.h"
#include "fx/Blackout.h"
#include "fx/Blur.h"
#include "fx/Chaser.h"
#include "fx/ColorBar.h"
#include "fx/DeepSpace.h"
#include "fx/Drops.h"
#include "fx/Strobe.h"
#include "fx/Fire.h"
#include "fx/Fireworks.h"
#include "fx/Glitter.h"
#include "fx/Jelly.h"
#include "fx/Juggle.h"
#include "fx/Matrix.h"
#include "fx/Orbit.h"
#include "fx/PeakMeter.h"
#include "fx/Photons.h"
#include "fx/Rainbow.h"
#include "fx/Ripple.h"
#include "fx/Scroller.h"
#include "fx/Sinelon.h"
#include "fx/SineMeter.h"
#include "fx/Spectrum.h"
#include "fx/Vertigo.h"
#include "fx/Volcane.h"

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
        void addFx(Fx *fx1 = nullptr, Fx *fx2 = nullptr, Fx *fx3 = nullptr) {
            Fx *fx = new Multiplex(fx1, fx2, fx3);
            randomFxIndexes.push_back(fxs.size());
            fxs.push_back(fx);
        }
        #endif
        #if defined(ARDUINO_TEENSY41)
        const static uint8_t CH1_PIN = 17;
        const static uint8_t CH2_PIN = 14;
        const static uint8_t CH3_PIN = 35;
        const static uint8_t CH4_PIN = 1;
        const static uint8_t CH5_PIN = 24;
        const static uint8_t CH6_PIN = 29;
        void addFx(Fx *fx1 = nullptr, Fx *fx2 = nullptr, Fx *fx3 = nullptr, Fx *fx4 = nullptr, Fx *fx5 = nullptr, Fx *fx6 = nullptr) {
            Fx *fx = new Multiplex(fx1, fx2, fx3, fx4, fx5, fx6);
            randomFxIndexes.push_back(fxs.size());
            fxs.push_back(fx);
        }
        #endif

        void addStrip(PhysicalStrip *strip) {
            strips.push_back(strip);
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
        void fadeOut() {
            for (Strip *strip : strips) {
                strip->fade(1);
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
