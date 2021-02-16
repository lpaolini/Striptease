#include "Controller.h"

Controller::Controller(
    Stage *stage,
    AudioSensor *audioSensor,
    State *state
) {
    this->stage = stage;
    this->audioSensor = audioSensor;
    this->state = state;
}

void Controller::setup() {
    setInput(line, false);
    brightness->init();
    pause();
    selectFx(0);
    if (SHOW_STATS) {
        statsTimer.reset();
    }
}

void Controller::loop() {
    if (mode == STOP) {
        stage->fadeOut();
    } else {
        if (mode == PLAY) {
            bool signalTrigger = !audioSensor->mono->signalDetected || audioSensor->mono->beatDetected;
            if (!playMode.manual && signalTrigger) {
                if (cycleTimer.isElapsed()) {
                    if (playMode.shuffle) {
                        selectRandomFx();
                    } else {
                        selectNextFx();
                    }
                }
            }
            stage->getFx(fx)->loopFlush();
        } else {
            if (modeTimer.isElapsed()) {
                reset();
            } else {
                switch (mode) {
                    case SET_FX_SPEED:
                        stage->getSpeedMeterFx()->loopFlush();
                        break;
                    case SET_CYCLE_SPEED:
                        stage->getCycleSpeedFx()->loopFlush();
                        break;
                    case SET_MIC_GAIN:
                        stage->getMicGainMeterFx()->loopFlush();
                        break;
                    case SET_INPUT_LEVEL:
                        stage->getInputLevelMeterFx()->loop();
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if (statsTimer.isElapsed()) {
        Serial.print("FPS: ");
        Serial.println(FastLED.getFPS());
        audioSensor->printStats();
    }

    brightness->loop();
    
    FastLED.show();
}

void Controller::setMode(Mode mode, unsigned long duration) {
    this->mode = mode;
    switch (mode) {
        case PLAY:
            modeTimer.stop();
            break;
        case SET_MIC_GAIN:
            modeTimer.reset(duration > 0 ? duration : SENSITIVITY_TIMER_DURATION);
            break;
        case SET_INPUT_LEVEL:
            modeTimer.reset(duration > 0 ? duration : SENSITIVITY_TIMER_DURATION);
            break;
        case SET_CYCLE_SPEED:
            modeTimer.reset(CYCLE_SPEED_TIMER_DURATION);
            break;
        case SET_FX_SPEED:
            modeTimer.reset(FX_SPEED_TIMER_DURATION);
            break;
        default:
            break;
    }
    info();
}

void Controller::setInput(Input input, bool feedback = true) {
    this->input = input;
    switch (input) {
        case mic:
            if (feedback) {
                setMode(SET_MIC_GAIN);
            }
            audioSensor->setMicInput();
            break;
        case line:
            if (feedback) {
                setMode(SET_INPUT_LEVEL);
            }
            audioSensor->setLineInput();
            break;
    }
}

void Controller::setLineInput(uint8_t level) {
    setInput(line, false);
    audioSensor->setLineInLevel(level);
}

void Controller::setMicInput(uint8_t gain) {
    setInput(mic, false);
    audioSensor->setMicGain(gain);
}

void Controller::toggleInput() {
    switch (input) {
        case mic:
            if (mode == SET_MIC_GAIN) {
                setInput(line, true);
            } else {
                setMode(SET_MIC_GAIN, INPUT_TIMER_DURATION);
            }
            break;
        case line:
            if (mode == SET_INPUT_LEVEL) {
                setInput(mic, true);
            } else {
                setMode(SET_INPUT_LEVEL, INPUT_TIMER_DURATION);
            }
            break;
    }
}

void Controller::increaseInputSensitivity() {
    switch (input) {
        case mic:
            increaseMicGain();
            break;
        case line:
            increaseLineInLevel();
            break;
    }
}

void Controller::increaseMicGain() {
    if (mode == SET_MIC_GAIN) {
        audioSensor->increaseMicGain();
    } else {
        setMode(SET_MIC_GAIN);
    }
}

void Controller::increaseLineInLevel() {
    if (mode == SET_INPUT_LEVEL) {
        audioSensor->increaseLineInLevel();
    } else {
        setMode(SET_INPUT_LEVEL);
    }
}

void Controller::decreaseInputSensitivity() {
    switch (input) {
        case mic:
            decreaseMicGain();
            break;
        case line:
            decreaseLineInLevel();
            break;
    }
}

void Controller::decreaseMicGain() {
    if (mode == SET_MIC_GAIN) {
        audioSensor->decreaseMicGain();
    } else {
        setMode(SET_MIC_GAIN);
    }
}

void Controller::decreaseLineInLevel() {
    if (mode == SET_INPUT_LEVEL) {
        audioSensor->decreaseLineInLevel();
    } else {
        setMode(SET_INPUT_LEVEL);
    }
}

void Controller::resetCycleTimer() {
    float delay = max(100, 1000 * pow(state->linearCycleSpeed, 2) * MAX_PATTERN_DELAY_S);
    cycleTimer.reset(delay);
}

void Controller::info() {
    Serial.print("Mode: ");
    switch (mode) {
        case PLAY:
            if (playMode.manual) {
                Serial.print("manual");
            } else {
                Serial.print("auto");
                if (playMode.shuffle) {
                    Serial.print(", shuffle");
                } else {
                    Serial.print(", sequential");
                }
                Serial.print(", cycle speed: ");
                Serial.print(state->getCycleSpeed());
            }
            Serial.print(", fx: ");
            Serial.print(fx + 1);
            Serial.print("/");
            Serial.print(stage->getFxCount());
            Serial.print(", fx speed: ");
            Serial.print(state->getFxSpeed());
            Serial.println();
            break;
        case STOP:
            Serial.println("stop");
            break;
        case SET_MIC_GAIN:
            Serial.println("set mic gain");
            break;
        case SET_INPUT_LEVEL:
            Serial.println("set line in level");
            break;
        case SET_CYCLE_SPEED:
            Serial.println("set cycle speed");
            break;
        case SET_FX_SPEED:
            Serial.println("set fx speed:");
            break;
        default:
            break;
    }
}

void Controller::feedback(uint8_t count) {
    brightness->blink(count);
}

void Controller::reset() {
    setMode(PLAY);
    resetCycleTimer();
    stage->getFx(fx)->reset();
}

void Controller::increaseBrightness() {
    brightness->increase();
}

void Controller::decreaseBrightness() {
    brightness->decrease();
}

void Controller::setParam(uint8_t value) {
    switch (mode) {
        case STOP:
            selectFx(value - 1);
            break;
        case PLAY:
            selectFx(value - 1);
            break;
        case SET_CYCLE_SPEED:
            setCycleSpeed(value);
            break;
        case SET_FX_SPEED:
            setFxSpeed(value);
            break;
        default:
            break;
    }
}

void Controller::increaseParam() {
    switch (mode) {
        case SET_MIC_GAIN:
            increaseMicGain();
            break;
        case SET_INPUT_LEVEL:
            increaseLineInLevel();
            break;
        case SET_CYCLE_SPEED:
            increaseCycleSpeed();
            break;
        default:
            increaseFxSpeed();
            break;
    }
}

void Controller::decreaseParam() {
    switch (mode) {
        case SET_MIC_GAIN:
            decreaseMicGain();
            break;
        case SET_INPUT_LEVEL:
            decreaseLineInLevel();
            break;
        case SET_CYCLE_SPEED:
            decreaseCycleSpeed();
            break;
        default:
            decreaseFxSpeed();
            break;
    }
}

void Controller::saveParam() {
    uint8_t previous = EEPROM.read(fx);
    uint8_t current = state->getFxSpeed();
    if (current != previous) {
        EEPROM.write(fx, current);
    }
}

void Controller::loadParam() {
    uint8_t previous = min(EEPROM.read(fx), 100);
    state->setFxSpeed(previous ? previous : 50);
}
            
void Controller::selectFx(uint8_t fx) {
    saveParam();
    this->fx = fx;
    loadParam();
    feedback();
    reset();
}

void Controller::selectPreviousFx() {
    selectFx(stage->getPrevFxIndex(fx));
}

void Controller::selectNextFx() {
    selectFx(stage->getNextFxIndex(fx));
}

void Controller::selectRandomFx() {
    selectFx(stage->getRandomFxIndex());
}

void Controller::play() {
    playMode.manual = false;
    run();
}

void Controller::sequential() {
    playMode.shuffle = false;
    play();
}

void Controller::shuffle() {
    playMode.shuffle = true;
    play();
}

void Controller::pause() {
    playMode.manual = true;
    run();
}

void Controller::playPause() {
    playMode.manual = !playMode.manual;
    run();
}

void Controller::run() {
    if (mode == STOP) {
        reset();
    } else {
        info();
    }
    feedback(playMode.manual ? 1 : playMode.shuffle ? 3 : 2);
}

void Controller::stop() {
    setMode(STOP);
}

void Controller::fxSpeed() {
    if (mode == SET_FX_SPEED) {
        reset();
    } else {
        setMode(SET_FX_SPEED);
    }
}

void Controller::setFxSpeed(uint8_t speed) {
    state->setFxSpeed(10 * MIN_MAX(speed, 0, 10));
    setMode(SET_FX_SPEED);
}

void Controller::decreaseFxSpeed() {
    if (mode == SET_FX_SPEED) {
        state->decreaseFxSpeed();
        modeTimer.reset();
    } else {
        setMode(SET_FX_SPEED);
    }
}

void Controller::increaseFxSpeed() {
    if (mode == SET_FX_SPEED) {
        state->increaseFxSpeed();
        modeTimer.reset();
    } else {
        setMode(SET_FX_SPEED);
    }
}

void Controller::cycleSpeed() {
    if (mode == SET_CYCLE_SPEED) {
        reset();
    } else {
        setMode(SET_CYCLE_SPEED);
    }
}

void Controller::setCycleSpeed(uint8_t speed) {
    state->setCycleSpeed(10 * MIN_MAX(speed, 0, 10));
    setMode(SET_CYCLE_SPEED);
}

void Controller::increaseCycleSpeed() {
    if (mode == SET_CYCLE_SPEED) {
        state->increaseCycleSpeed();
        modeTimer.reset();
    } else {
        setMode(SET_CYCLE_SPEED);
    }
}

void Controller::decreaseCycleSpeed() {
    if (mode == SET_CYCLE_SPEED) {
        state->decreaseCycleSpeed();
        modeTimer.reset();
    } else {
        setMode(SET_CYCLE_SPEED);
    }
}
