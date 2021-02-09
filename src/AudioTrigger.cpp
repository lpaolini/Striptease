#include "AudioTrigger.h"

AudioTrigger::AudioTrigger(AudioChannel *audioChannel) {
    this->audioChannel = audioChannel;
}

void AudioTrigger::reset() {
    timer = 0;
}

bool AudioTrigger::triggered(float noSignalEventsPerSecond = 0, float signalEventsPerSecond = 0) {
    unsigned long us = timer;
    bool trigger = audioChannel->signalDetected
        ? audioChannel->beatDetected || random(1e6) < (signalEventsPerSecond * us)
        : random(1e6) < (noSignalEventsPerSecond * us);
    reset();
    return trigger;
}
