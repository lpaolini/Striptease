#include "MyStage.h"

MyStage::MyStage(AudioSensor *audioSensor, State *state) {
    PhysicalStrip *left = new PhysicalStrip(leftArray, STRIP_LEFT_DENSITY);
    PhysicalStrip *right = new PhysicalStrip(rightArray, STRIP_RIGHT_DENSITY);
    PhysicalStrip *top = new PhysicalStrip(topArray, STRIP_TOP_DENSITY);
    PhysicalStrip *xmasTree = new PhysicalStrip(xmasTreeArray, STRIP_XMASTREE_DENSITY);

    addStrip(left);
    addStrip(right);
    addStrip(top);
    addStrip(xmasTree);

    Strip *front = new JoinedStrip(new ReversedStrip(left), right, 2);
    Strip *subLeft = new SubStrip(left, 15, 79);
    Strip *subRight = new SubStrip(right, 15, 79);

    Fx *topBlackout = new Blackout(top);
    Fx *xmasBlackout = new Blackout(xmasTree);

    addFx(new Rainbow(front, state), new Rainbow(top, state), new Rainbow(xmasTree, state)); 
    addFx(new Volcane(left, audioSensor->left, state), new Volcane(right, audioSensor->right, state), topBlackout, new Volcane(xmasTree, audioSensor->mono, state));
    addFx(new Jelly(left, audioSensor->left, state), new Jelly(right, audioSensor->right, state), new Jelly(xmasTree, audioSensor->mono, state), new Jelly(top, audioSensor->mono, state));
    addFx(new Chaser(left, audioSensor->left, state), new Chaser(right, audioSensor->right, state), topBlackout, new Chaser(xmasTree, audioSensor->mono, state), new Chaser(top, audioSensor->mono, state));
    addFx(new Glitter(front, state), new Glitter(top, state), new Glitter(xmasTree, state));
    addFx(new Orbit(left, state), new Orbit(right, state, 120), topBlackout, new Orbit(xmasTree, state));
    addFx(new VU1(left, audioSensor->left), new VU1(right, audioSensor->right), new VU1(xmasTree, audioSensor->mono), topBlackout);
    addFx(new Elastic(left, audioSensor->left, state), new Elastic(right, audioSensor->right, state), new Elastic(top, audioSensor->mono, state), new Elastic(xmasTree, audioSensor->mono, state));
    addFx(new Sinelon(left, state), new Sinelon(right, state), new Sinelon(xmasTree, state), new Sinelon(top, state));
    addFx(new SineMeter(left, audioSensor->left, state), new SineMeter(right, audioSensor->right, state), new SineMeter(xmasTree, audioSensor->mono, state), topBlackout);
    addFx(new Matrix(front, audioSensor->mono, state), new PeakMeter(subLeft, audioSensor->left), new PeakMeter(subRight, audioSensor->right), topBlackout, new PeakMeter(xmasTree, audioSensor->mono));
    addFx(new Ripple(left, audioSensor->left, state), new Ripple(right, audioSensor->right, state), new Ripple(top, audioSensor->mono, state), new Ripple(xmasTree, audioSensor->mono, state));
    addFx(new Strobe(left, audioSensor->left, state), new Strobe(right, audioSensor->right, state), new Strobe(top, audioSensor->mono, state), new Strobe(xmasTree, audioSensor->mono, state));
    addFx(new Ants(left, audioSensor->left, state), new Ants(right, audioSensor->right, state), new Ants(xmasTree, audioSensor->mono, state), topBlackout);
    addFx(new Photons(left, audioSensor->left, state), new Photons(right, audioSensor->right, state), new Photons(xmasTree, audioSensor->mono, state), new Ripple(top, audioSensor->mono, state));
    addFx(new Fire(left, audioSensor->left), new Fire(right, audioSensor->right), new Fire(xmasTree, audioSensor->mono), topBlackout);
    addFx(new Beat(left, audioSensor->left), new Beat(right, audioSensor->right), new Beat(xmasTree, audioSensor->mono), topBlackout);
    addFx(new Blur(left), new Blur(right), new Blur(xmasTree), topBlackout);
    addFx(new Juggle(left, state), new Juggle(right, state), new Juggle(xmasTree, state), new Juggle(top, state));
    addFx(new Matrix(front, audioSensor->mono, state), new Matrix(xmasTree, audioSensor->mono, state), new Matrix(top, audioSensor->mono, state));
    addFx(new Drops(left, audioSensor->left, state), new Drops(right, audioSensor->right, state), new Drops(top, audioSensor->mono, state), new Drops(xmasTree, audioSensor->mono, state));
    addFx(new Scroller(left, audioSensor->left, state), new Scroller(right, audioSensor->right, state), new Scroller(xmasTree, audioSensor->mono, state), topBlackout);
    addFx(new Fireworks(left, audioSensor->left, state), new Fireworks(right, audioSensor->right, state), new Fireworks(top, audioSensor->mono, state), new Fireworks(xmasTree, audioSensor->mono, state));
    addFx(new Vertigo(left, audioSensor->left, state), new Vertigo(right, audioSensor->right, state), topBlackout, new Vertigo(xmasTree, audioSensor->mono, state));
    addFx(new DeepSpace(front, audioSensor->mono, state), topBlackout, xmasBlackout);
    addFx(new ColorBar(front, state), new ColorBar(top, state), xmasBlackout);

    addFx(
        new Matrix(front, audioSensor->mono, state), 
        new Fireworks(front->buffered(), audioSensor->mono, state), 
        new Drops(left->buffered(), audioSensor->left, state), 
        new Drops(right->buffered(), audioSensor->right, state), 
        new VU2(left->buffered(), audioSensor->left, 1, 500), 
        new VU2(right->buffered(), audioSensor->right, 1, 500),
        topBlackout,
        xmasBlackout
    );

    addFx(
        new Ripple(front, audioSensor->mono, state),
        new Ants(left->buffered(), audioSensor->left, state), new Ants(right->buffered(), audioSensor->right, state),
        topBlackout
    );

    addFx(
        new DeepSpace(front, audioSensor->mono, state), 
        new PeakMeter(subLeft->buffered(), audioSensor->left), 
        new PeakMeter(subRight->buffered(), audioSensor->right), 
        topBlackout, 
        xmasBlackout
    );

    addFx(
        new DeepSpace(front, audioSensor->mono, state), 
        new Photons(subLeft->buffered(), audioSensor->left, state), 
        new Photons(subRight->buffered(), audioSensor->right, state),
        topBlackout, 
        xmasBlackout
    );

    addFx(new Spiral(front, state, 50, 2, .3));

    setCycleSpeedFx(new CycleSpeed(left, state), new CycleSpeed(right, state));
    setSpeedMeterFx(new SpeedMeter(left, state), new SpeedMeter(right, state));
    setMicGainMeterFx(new MicGainMeter(left, audioSensor->left, audioSensor), new MicGainMeter(right, audioSensor->right, audioSensor));
    setInputLevelMeterFx(new InputLevelMeter(left, audioSensor->left, audioSensor), new InputLevelMeter(right, audioSensor->right, audioSensor));

    FastLED.addLeds<WS2812SERIAL, STRIP_LEFT_PIN, BRG>(leftArray, leftArray.size());
    FastLED.addLeds<WS2812SERIAL, STRIP_RIGHT_PIN, BRG>(rightArray, rightArray.size());
    FastLED.addLeds<WS2812SERIAL, STRIP_TOP_PIN, BRG>(topArray, topArray.size());
    FastLED.addLeds<WS2812SERIAL, STRIP_XMASTREE_PIN, BRG>(xmasTreeArray, xmasTreeArray.size());
    FastLED.setMaxPowerInMilliWatts(1000 * MAX_WATTS);
    FastLED.setCorrection(TypicalSMD5050);
}
