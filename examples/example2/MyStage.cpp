#include "MyStage.h"

MyStage::MyStage(AudioSensor *audioSensor, State *state) {
    PhysicalStrip *left = new PhysicalStrip(leftArray, STRIP_LEFT_DENSITY);
    PhysicalStrip *right = new PhysicalStrip(rightArray, STRIP_RIGHT_DENSITY);

    addStrip(left);
    addStrip(right);

    addFx(new Rainbow(left, state), new Rainbow(right, state, 128));
    addFx(new Volcane(left, audioSensor->left, state), new Volcane(right, audioSensor->right, state));
    addFx(new Jelly(left, audioSensor->left, state), new Jelly(right, audioSensor->right, state));
    addFx(new Chaser(left, audioSensor->left, state), new Chaser(right, audioSensor->right, state));
    addFx(new Glitter(left, state), new Glitter(right, state));
    addFx(new Orbit(left, state), new Orbit(right, state, 120));
    addFx(new VU1(left, audioSensor->left), new VU1(right, audioSensor->right));
    addFx(new Elastic(left, audioSensor->left, state), new Elastic(right, audioSensor->right, state));
    addFx(new Sinelon(left, state), new Sinelon(right, state));
    addFx(new SineMeter(left, audioSensor->left, state), new SineMeter(right, audioSensor->right, state));
    addFx(new PeakMeter(left, audioSensor->left), new PeakMeter(right, audioSensor->right));
    addFx(new Ripple(left, audioSensor->left, state), new Ripple(right, audioSensor->right, state));
    addFx(new Strobe(left, audioSensor->left, state), new Strobe(right, audioSensor->right, state));
    addFx(new Ants(left, audioSensor->left, state), new Ants(right, audioSensor->right, state));
    addFx(new Photons(left, audioSensor->left, state), new Photons(right, audioSensor->right, state));
    addFx(new Fire(left, audioSensor->left), new Fire(right, audioSensor->right));
    addFx(new Beat(left, audioSensor->left), new Beat(right, audioSensor->right));
    addFx(new Blur(left), new Blur(right));
    addFx(new Juggle(left, state), new Juggle(right, state));
    addFx(new Matrix(left, audioSensor->left), new Matrix(right, audioSensor->right));
    addFx(new Drops(left, audioSensor->left, state), new Drops(right, audioSensor->right, state));
    addFx(new Scroller(left, audioSensor->left, state), new Scroller(right, audioSensor->right, state));
    addFx(new Fireworks(left, audioSensor->left, state), new Fireworks(right, audioSensor->right, state));
    addFx(new Vertigo(left, audioSensor->left, state), new Vertigo(right, audioSensor->right, state));
    addFx(new DeepSpace(left, audioSensor->left, state), new DeepSpace(right, audioSensor->right, state));

    setCycleSpeedFx(new CycleSpeed(left, state), new CycleSpeed(right, state));
    setSpeedMeterFx(new SpeedMeter(left, state), new SpeedMeter(right, state));
    setMicGainMeterFx(new MicGainMeter(left, audioSensor->left, audioSensor), new MicGainMeter(right, audioSensor->right, audioSensor));
    setInputLevelMeterFx(new InputLevelMeter(left, audioSensor->left, audioSensor), new InputLevelMeter(right, audioSensor->right, audioSensor));

    FastLED.addLeds<WS2812SERIAL, STRIP_LEFT_PIN, BRG>(leftArray, leftArray.size());
    FastLED.addLeds<WS2812SERIAL, STRIP_RIGHT_PIN, BRG>(rightArray, rightArray.size());
    FastLED.setMaxPowerInMilliWatts(1000 * MAX_WATTS);
}
