#include "MyStage.h"

MyStage::MyStage(AudioSensor *audioSensor, State *state) {

    Strip *left = addStrip(leftArray, STRIP_LEFT_DENSITY);
    Strip *right = addStrip(rightArray, STRIP_RIGHT_DENSITY);
    Strip *top = addStrip(topArray, STRIP_TOP_DENSITY);
    Strip *xmasTree = addStrip(xmasTreeArray, STRIP_XMASTREE_DENSITY);

    Strip *front = new JoinedStrip(new ReversedStrip(left), right, 2);
    Strip *subLeft = new SubStrip(left, 15, 79);
    Strip *subRight = new SubStrip(right, 15, 79);
    Strip *topLeft = new ReversedStrip(new SubStrip(top, 0, 83));
    Strip *topRight = new SubStrip(top, 85, 168);

    Fx *frontBlackout = new Blackout(front);
    Fx *topBlackout = new Blackout(top);
    Fx *xmasBlackout = new Blackout(xmasTree);

    CRGB blueBackgroundColor = CHSV(160, 255, 40);
    CRGB redBackgroundColor = CHSV(0, 255, 40);

    // Fx #1

    addFx(
        new Rainbow(front, state),
        new Rainbow(top, state),
        new Rainbow(xmasTree, state)
    );

    // Fx #2

    addFx(
        new Volcane(left, audioSensor->left, state),
        new Volcane(right, audioSensor->right, state),
        topBlackout,
        new Volcane(xmasTree, audioSensor->mono, state)
    );

    // Fx #3

    addFx(
        new Jelly(left, audioSensor->left, state),
        new Jelly(right, audioSensor->right, state),
        new Jelly(top, audioSensor->mono, state),
        new Jelly(xmasTree, audioSensor->mono, state)
    );

    // Fx #4

    addFx(
        new Chaser(left, audioSensor->left, state),
        new Chaser(right, audioSensor->right, state),
        new Chaser(top, audioSensor->mono, state),
        new Chaser(xmasTree, audioSensor->mono, state)
    );

    // Fx #5

    addFx(
        new Glitter(front, state),
        new Glitter(top, state),
        new Glitter(xmasTree, state)
    );

    // Fx #6

    addFx(
        new VU1(left, audioSensor->left, state),
        new VU1(right, audioSensor->right, state),
        new VU1(topLeft, audioSensor->left, state),
        new VU1(topRight, audioSensor->right, state),
        new Jelly(xmasTree, audioSensor->mono, state)
    );

    // Fx #7

    addFx(
        new Elastic(front, audioSensor->mono, state),
        new Elastic(top, audioSensor->mono, state),
        new Elastic(xmasTree, audioSensor->mono, state)
    );

    // Fx #8

    addFx(
        new Sinelon(front, state),
        new VU2(left->overlay(), audioSensor->left, 5, 1000, CRGB::LimeGreen),
        new VU2(right->overlay(), audioSensor->right, 5, 1000, CRGB::LimeGreen),
        new Sinelon(top, state),
        new Sinelon(xmasTree, state)
    );

    // Fx #9

    addFx(
        new SineMeter(left, audioSensor->left, state),
        new SineMeter(right, audioSensor->right, state),
        topBlackout,
        new SineMeter(xmasTree, audioSensor->mono, state)
    );

    // Fx #10

    addFx(
        new Matrix(front, audioSensor->mono, state),
        new PeakMeter(subLeft, audioSensor->left),
        new PeakMeter(subRight, audioSensor->right),
        topBlackout,
        new Ripple(xmasTree, audioSensor->mono, state, redBackgroundColor)
    );

    // Fx #11

    addFx(
        new Ripple(front, audioSensor->mono, state, blueBackgroundColor),
        new VU2(left->overlay(), audioSensor->left, 1, 1000, CRGB::Blue),
        new VU2(right->overlay(), audioSensor->right, 1, 1000, CRGB::Blue),
        new Ripple(top, audioSensor->mono, state, blueBackgroundColor),
        new Ripple(xmasTree, audioSensor->mono, state, blueBackgroundColor)
    );

    // Fx #12

    addFx(
        new Strobe(left, audioSensor->left, state),
        new Strobe(right, audioSensor->right, state),
        new Strobe(top, audioSensor->mono, state),
        new Strobe(xmasTree, audioSensor->mono, state)
    );

    // Fx #13

    addFx(
        new Ants(left, audioSensor->left, state),
        new Ants(right, audioSensor->right, state),
        topBlackout,
        new Ants(xmasTree, audioSensor->mono, state)
    );

    // Fx #14

    addFx(
        new DeepSpace(front, audioSensor->mono, state, CRGB::DarkRed, CRGB::HotPink),
        new Jelly(left->overlay(), audioSensor->left, state),
        new Jelly(right->overlay(), audioSensor->right, state),
        new VU2(left->overlay(), audioSensor->left, 1, 200, CRGB::LimeGreen),
        new VU2(right->overlay(), audioSensor->right, 1, 200, CRGB::LimeGreen),
        new Ripple(top, audioSensor->mono, state, blueBackgroundColor),
        new Photons(xmasTree, audioSensor->mono, state)
    );

    // Fx #15

    addFx(
        new Fire(left, audioSensor->left),
        new Fire(right, audioSensor->right),
        topBlackout,
        new Fire(xmasTree, audioSensor->mono)
    );

    // Fx #16

    addFx(
        new Beat(left, audioSensor->left),
        new Beat(right, audioSensor->right),
        topBlackout,
        new Beat(xmasTree, audioSensor->mono)
    );

    // Fx #17

    addFx(
        new Blackout(front),
        new Blur(left->overlay()),
        new Blur(right->overlay()),
        new Ants(left->overlay(), audioSensor->left, state),
        new Ants(right->overlay(), audioSensor->right, state),
        topBlackout,
        new Blur(xmasTree)
    );

    // Fx #18

    addFx(
        new Blackout(front),
        new Juggle(left->overlay(), state),
        new Juggle(right->overlay(), state),
        new Vertigo(left->overlay(), audioSensor->left, state),
        new Vertigo(right->overlay(), audioSensor->right, state),
        new Juggle(top, state),
        new Juggle(xmasTree, state)
    );

    // Fx #19

    addFx(
        new Matrix(front, audioSensor->mono, state),
        new Ants(front->overlay(), audioSensor->mono, state),
        new Matrix(top, audioSensor->mono, state),
        new Matrix(xmasTree, audioSensor->mono, state)
    );

    // Fx #20

    addFx(
        new Drops(left, audioSensor->left, state),
        new Drops(right, audioSensor->right, state),
        new Spiral(front->overlay(), state, 10, 2, .3),
        new Drops(top, audioSensor->mono, state),
        new Drops(xmasTree, audioSensor->mono, state)
    );

    // Fx #21

    addFx(
        new Blackout(left),
        new Blackout(right),
        new Scroller(left->overlay(), audioSensor->left, state),
        new Scroller(right->overlay(), audioSensor->right, state),
        new VU2(left->overlay(), audioSensor->left, 1, 1000, CRGB::White),
        new VU2(right->overlay(), audioSensor->right, 1, 1000, CRGB::White),
        new Ripple(xmasTree, audioSensor->mono, state),
        topBlackout
    );

    // Fx #22

    addFx(
        new Fireworks(left, audioSensor->left, state),
        new Fireworks(right, audioSensor->right, state),
        new Fireworks(top, audioSensor->mono, state),
        new Fireworks(xmasTree, audioSensor->mono, state)
    );

    // Fx #23

    addFx(
        new Vertigo(left, audioSensor->left, state),
        new Vertigo(right, audioSensor->right, state),
        topBlackout,
        new Ripple(xmasTree, audioSensor->mono, state)
    );

    // Fx #24

    addFx(
        frontBlackout,
        new DeepSpace(front->overlay(), audioSensor->mono, state, 0x800000, 0x000020),
        topBlackout,
        xmasBlackout
    );

    // Fx #25

    addFx(
        new Matrix(front, audioSensor->mono, state),
        new Fireworks(front->overlay(), audioSensor->mono, state),
        new Drops(left->overlay(), audioSensor->left, state),
        new Drops(right->overlay(), audioSensor->right, state),
        new VU2(left->overlay(), audioSensor->left, 1, 500),
        new VU2(right->overlay(), audioSensor->right, 1, 500),
        topBlackout,
        new Drops(xmasTree, audioSensor->mono, state)
    );

    // Fx #26

    addFx(
        new Elastic(front, audioSensor->mono, state),
        new VU2(left->overlay(), audioSensor->left, 1, 1000),
        new VU2(right->overlay(), audioSensor->right, 1, 1000),
        topBlackout,
        new Sparks(xmasTree, audioSensor->mono, state)
    );

    // Fx #27

    addFx(
        new Ripple(front, audioSensor->mono, state, blueBackgroundColor),
        new Ants(left->overlay(), audioSensor->left, state),
        new Ants(right->overlay(), audioSensor->right, state),
        topBlackout,
        new Ants(xmasTree, audioSensor->mono, state)
    );

    // Fx #28

    addFx(
        new DeepSpace(front, audioSensor->mono, state, 0x000040, 0x101010),
        new VU1(left->overlay(), audioSensor->left, state),
        new VU1(right->overlay(), audioSensor->right, state),
        topBlackout,
        new Drops(xmasTree, audioSensor->mono, state)
    );

    // Fx #29

    addFx(
        new Ripple(top, audioSensor->mono, state, blueBackgroundColor),
        new Spectrum(topLeft->overlay(), audioSensor->left),
        new Spectrum(topRight->overlay(), audioSensor->right),
        new Ripple(front, audioSensor->mono, state, blueBackgroundColor),
        new Spectrum(left->overlay(), audioSensor->left),
        new Spectrum(right->overlay(), audioSensor->right),
        new Ripple(xmasTree, audioSensor->mono, state, blueBackgroundColor)
    );

    // Fx #30

    addFx(
        new RippleReflections(front, audioSensor->mono, state),
        topBlackout,
        new Drops(xmasTree, audioSensor->mono, state)
    );

    // Fx #31
    
    addFx(
        new RainbowMelt(front, audioSensor->mono, state),
        new VU2(left->overlay(), audioSensor->left, 5, 1000, CRGB::White),
        new VU2(right->overlay(), audioSensor->right, 5, 1000, CRGB::White),
        new RainbowMelt(top, audioSensor->mono, state),
        new RainbowMelt(xmasTree, audioSensor->mono, state)
    );

    // Fx #32
    
    addFx(
        new FastPulse(front, audioSensor->mono, state),
        new VU1(left->overlay(), audioSensor->left, state),
        new VU1(right->overlay(), audioSensor->right, state),
        new FastPulse(top, audioSensor->mono, state),
        new FastPulse(xmasTree, audioSensor->mono, state)
    );

    // Fx #33
    
    addFx(
        new MarchingRainbow(front, audioSensor->mono, state),
        new MarchingRainbow(top, audioSensor->mono, state),
        new MarchingRainbow(xmasTree, audioSensor->mono, state)
    );

    // Fx #34
    
    addFx(
        new ColorTwinkles(front, audioSensor->mono, state),
        topBlackout,
        new ColorTwinkles(xmasTree, audioSensor->mono, state)
    );

    // Fx #35
    
    addFx(
        new SubtleWave(left, audioSensor->left, state),
        new SubtleWave(right, audioSensor->right, state),
        new Spiral(front->overlay(), state, 10, 2, .3),
        topBlackout,
        new Drops(xmasTree, audioSensor->mono, state)
    );

    // Fx #36
    
    addFx(
        new Sparks(left, audioSensor->left, state),
        new Sparks(right, audioSensor->right, state),
        new Sparks(top, audioSensor->mono, state),
        new Background(xmasTree, blueBackgroundColor),
        new Sparks(xmasTree->overlay(), audioSensor->mono, state, CRGB::White, CRGB::Red)
    );

    // Fx #37
    
    addFx(
        new Traffic(front, audioSensor->mono, state),
        new Traffic(top, audioSensor->mono, state),
        topBlackout,
        new Drops(xmasTree, audioSensor->mono, state)
    );

    // Fx #38
    
    addFx(
        new Orbit(left, state),
        new Orbit(right, state, 120),
        topBlackout,
        new Orbit(xmasTree, state)
    );

    setCycleSpeedFx(new CycleSpeed(left, state), new CycleSpeed(right, state));
    setSpeedMeterFx(new SpeedMeter(left, state), new SpeedMeter(right, state));
    setMicGainMeterFx(new MicGainMeter(left, audioSensor->left, audioSensor), new MicGainMeter(right, audioSensor->right, audioSensor));
    setInputLevelMeterFx(new InputLevelMeter(left, audioSensor->left, audioSensor), new InputLevelMeter(right, audioSensor->right, audioSensor));

    FastLED.addLeds<WS2812SERIAL, STRIP_LEFT_PIN, BRG>(leftArray, leftArray.size());
    FastLED.addLeds<WS2812SERIAL, STRIP_RIGHT_PIN, BRG>(rightArray, rightArray.size());
    FastLED.addLeds<WS2812SERIAL, STRIP_TOP_PIN, BRG>(topArray, topArray.size());
    FastLED.addLeds<WS2812SERIAL, STRIP_XMASTREE_PIN, BRG>(xmasTreeArray, xmasTreeArray.size());
    
    FastLED.setMaxPowerInMilliWatts(1000 * MAX_WATTS);
    FastLED.setCorrection(TypicalLEDStrip);
    // FastLED.setDither(BINARY_DITHER);
    // FastLED.setDither(DISABLE_DITHER);
}
