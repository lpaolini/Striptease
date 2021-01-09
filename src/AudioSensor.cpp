#include "AudioSensor.h"

AudioSensor::AudioSensor() {
    cpl = new AudioConnection(audioInput, 0, peak_L, 0);
    crl = new AudioConnection(audioInput, 0, rms_L, 0);
    cfl = new AudioConnection(audioInput, 0, fft_L, 0);
    cml = new AudioConnection(audioInput, 0, mixer, 0);
    cpr = new AudioConnection(audioInput, 1, peak_R, 0);
    crr = new AudioConnection(audioInput, 1, rms_R, 0);
    cfr = new AudioConnection(audioInput, 1, fft_R, 0);
    cmr = new AudioConnection(audioInput, 1, mixer, 1);
    cpm = new AudioConnection(mixer, peak_M);
    crm = new AudioConnection(mixer, rms_M);
    audioShield = new AudioControlSGTL5000();
    mixer.gain(0, 0.5);
    mixer.gain(1, 0.5);
}

void AudioSensor::setup() {
    AudioMemory(20);
    audioShield->enable();
    audioShield->volume(0);
    setLineInput();
}

void AudioSensor::loop() {
    left->loop(&peak_L, &rms_L, &fft_L);
    right->loop(&peak_R, &rms_R, &fft_R);
    mono->loop(&peak_M, &rms_M);
}

void AudioSensor::setMicInput() {
    audioShield->inputSelect(AUDIO_INPUT_MIC);
    audioShield->micGain(micGain);
    Serial.println("Mic input selected");
}

void AudioSensor::setMicGain(uint8_t micGain) {
    this->micGain = micGain;
    audioShield->micGain(micGain);
    Serial.print("Mic gain: ");
    Serial.println(micGain);
}

uint8_t AudioSensor::getMicGain() {
    return micGain;
}

void AudioSensor::increaseMicGain() {
    setMicGain(min(63, micGain + 1));
}

void AudioSensor::decreaseMicGain() {
    setMicGain(max(0, micGain - 1));
}

void AudioSensor::setLineInput() {
    audioShield->inputSelect(AUDIO_INPUT_LINEIN);
    audioShield->lineInLevel(lineInLevel);
    Serial.println("Line in input selected");
}

void AudioSensor::setLineInLevel(uint8_t lineInLevel) {
    this->lineInLevel = lineInLevel;
    audioShield->lineInLevel(lineInLevel);
    Serial.print("Line in level: ");
    Serial.println(lineInLevel);
}

uint8_t AudioSensor::getLineInLevel() {
    return lineInLevel;
}

void AudioSensor::increaseLineInLevel() {
    setLineInLevel(min(15, lineInLevel + 1));
}

void AudioSensor::decreaseLineInLevel() {
    setLineInLevel(max(0, lineInLevel - 1));
}

float AudioSensor::getNormalizedMicGain() {
    return float(micGain) / 63;
}

float AudioSensor::getNormalizedLineInLevel() {
    return float(lineInLevel) / 15;
}
