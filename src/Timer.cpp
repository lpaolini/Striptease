#include "Timer.h"

Timer::Timer(unsigned long duration, bool autoReset) {
    this->duration = duration;
    this->autoReset = autoReset;
    stop();
}

void Timer::stop() {
    running = false;
    last = millis();
}

void Timer::reset() {
    running = true;
    last = millis();
}

void Timer::reset(unsigned long duration) {
    this->duration = duration;
    reset();
}

bool Timer::isElapsed() {
    return duration > 0 && isElapsed(duration);
}

bool Timer::isElapsed(unsigned long duration) {
    if (running) {
        unsigned long current = millis();
        if (current - last > duration) {
            if (autoReset) {
                last += duration;
                if (current - last > duration) {
                    last = millis();
                }
            } else {
                running = false;
            }
            return true;
        }
    }
    return false;
}

bool Timer::isRunning() {
    return running;
}
