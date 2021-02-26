#define IRMP_INPUT_PIN                  22
#define IRMP_SUPPORT_SIRCS_PROTOCOL     1 // Enable SIRCS (Sony) IR protocol

#include <StripTease.h>

#include "MyStage.h"
#include "SonyRemote_RMD420.h"

AudioSensor *audioSensor = new AudioSensor();
State *state = new State();
Stage *stage = new MyStage(audioSensor, state);
Controller *controller = new Controller(stage, audioSensor, state);
Remote *remote = new SonyRemote_RMD420(controller);
SerialRemote *serialRemote = new SerialRemote(controller);


void init() {
    Serial.begin(115200);
    randomSeed(analogRead(0));
}

void setup() {
    init();
    audioSensor->setup();
    state->setup();
    controller->setup();
    controller->setMicInput(50);
    remote->setup();
    serialRemote->setup();
}

void loop() {
    audioSensor->loop();
    state->loop();
    controller->loop();
    remote->loop();
    serialRemote->loop();
}
