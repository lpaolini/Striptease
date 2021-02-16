#include "Beat.h"

Beat::Beat(Strip *strip, AudioChannel *audioChannel) : Fx(strip, audioChannel) {
    audioTrigger = new AudioTrigger(audioChannel);
    peak.setup(strip);
    peakHold.setup(strip);
    peakHoldSlow.setup(strip);
    reset();
}

Beat::~Beat() {
    delete audioTrigger;
}

void Beat::reset() {
    clear();
    uint16_t center = strip->center();

    peak.reset()
        .setColor(CRGB::Blue)
        .setPosition(center)
        .setFixedPointPosition(center)
        .setLowerBound(center)
        .setRange(0, 1)
        .setMirror(true)
        .setFill(true)
        .setShowWhenStable(true);
    
    peakHold.reset()
        .setColor(CRGB::Turquoise)
        .setPosition(center)
        .setFixedPointPosition(center)
        .setAcceleration(-100)
        .setLowerBound(center)
        .setRange(2, 5)
        .setMirror(true)
        .setShowWhenStable(true);

    peakHoldSlow.reset()
        .setColor(CRGB::Red)
        .setPosition(center)
        .setFixedPointPosition(center)
        .setAcceleration(25)
        .setLowerBound(center)
        .setRange(6, 7)
        .setMirror(true)
        .setShowWhenStable(true);

    timer.reset();
    audioTrigger->reset();
}

void Beat::loop() {
    strip->off();
    if (audioTrigger->triggered(1)) {
        if (timer.isElapsed()) {
            uint16_t pos = (1 + audioChannel->rms) * strip->center(); 
            peak.setPosition(max(peak.getPosition(), pos));
            peak.setVelocity(-30);
            peakHold.setPosition(max(peakHold.getPosition(), pos));
            peakHold.setVelocity(0);
            peakHoldSlow.setPosition(min(peakHoldSlow.getPosition(), pos));
            peakHoldSlow.setVelocity(25);
        }
    }

    peak.loop();
    peakHold.loop();
    peakHoldSlow.loop();
}
