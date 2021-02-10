#include "AudioTrigger.h"

AudioTrigger::AudioTrigger(AudioChannel *audioChannel) {
    this->audioChannel = audioChannel;
}

void AudioTrigger::reset() {
    beatDetected = false;
    timer = 0;
}

void AudioTrigger::loop() {
    beatDetected = beatDetected || audioChannel->beatDetected;
}

bool AudioTrigger::triggered(float noSignalEventsPerSecond, float signalEventsPerSecond) {
    unsigned long us = timer;
    bool trigger = audioChannel->signalDetected
        ? beatDetected || audioChannel->beatDetected || random(1e6) < (signalEventsPerSecond * us)
        : random(1e6) < (noSignalEventsPerSecond * us);
    reset();
    return trigger;
}
