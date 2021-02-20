#ifndef Controller_h
#define Controller_h

#include <Arduino.h>
#include <EEPROM.h>

#include "AudioSensor.h"
#include "Brightness.h"
#include "Fx.h"
#include "Stage.h"
#include "State.h"
#include "Strip.h"
#include "Timer.h"

#define MIN_MAX(v, vmin, vmax) max(vmin, min(vmax, v))

class Controller {
    private:
        enum Mode {STOP, PLAY, SET_MIC_GAIN, SET_INPUT_LEVEL, SET_CYCLE_SPEED, SET_FX_SPEED};
        enum Input {mic, line};
        static const uint16_t MAX_PATTERN_DELAY_S = 60;
        static const unsigned long INPUT_TIMER_DURATION = 5000;
        static const unsigned long SENSITIVITY_TIMER_DURATION = 60000;
        static const unsigned long FX_SPEED_TIMER_DURATION = 500;
        static const unsigned long CYCLE_SPEED_TIMER_DURATION = 3000;
        static const bool SHOW_STATS = false;
        Stage *stage;
        AudioSensor *audioSensor;
        State *state;
        uint16_t fx = 0;
        Brightness *brightness = new Brightness();
        struct PlayMode {
            bool manual = false;
            bool shuffle = false;
        } playMode;
        Input input;
        Mode mode = PLAY;
        Timer cycleTimer = Timer(0, false);
        Timer modeTimer = Timer(0, false);
        Timer statsTimer = Timer(10000, true);
        void saveParam();
        void loadParam();
        void resetCycleTimer();
        void increaseMicGain();
        void decreaseMicGain();
        void increaseLineInLevel();
        void decreaseLineInLevel();
        void run();

    public:
        Controller(
            Stage *stage,
            AudioSensor *audioSensor,
            State *state
        );
        void setup();
        void loop();

        void setMode(Mode mode = PLAY, unsigned long duration = 0);

        void setInput(Input input, bool feedback);
        void setLineInput(uint8_t level);
        void setMicInput(uint8_t gain);
        void toggleInput();
        void increaseInputSensitivity();
        void decreaseInputSensitivity();

        void info();
        void feedback(uint8_t count = 1);
        void reset();

        void increaseBrightness();
        void decreaseBrightness();

        void setParam(uint8_t value);
        void increaseParam();
        void decreaseParam();

        void selectFx(uint8_t fx);
        void selectPreviousFx();
        void selectNextFx();
        void selectRandomFx();
        void play();
        void sequential();
        void shuffle();
        void pause();
        void playPause();
        void stop();
        
        void cycleSpeed();
        void setCycleSpeed(uint8_t speed);
        void increaseCycleSpeed();
        void decreaseCycleSpeed();
        
        void fxSpeed();
        void setFxSpeed(uint8_t speed);
        void increaseFxSpeed();
        void decreaseFxSpeed();
};

#endif
