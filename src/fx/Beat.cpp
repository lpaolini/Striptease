#include "Beat.h"

Beat::Beat(Strip *strip, AudioChannel *audioChannel) {
    this->strip = strip;
    this->audioChannel = audioChannel;
    peak.setup(strip);
    peakHold.setup(strip);
    peakHoldSlow.setup(strip);
    reset();
}

void Beat::reset() {
    clear(strip);
    uint16_t center = strip->centerPos();

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
}

void Beat::loop() {
    strip->off();
    if (timer.isElapsed()) {
        if (audioChannel->beatDetected) {
            uint16_t pos = (1 + audioChannel->rms) * strip->centerPos(); 
            peak.setPosition(max(peak.getPosition(), pos));
            peak.setVelocity(-50);
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
