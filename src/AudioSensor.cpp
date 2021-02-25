#include "AudioSensor.h"

AudioSensor::AudioSensor() {
    patchPeakLeft = new AudioConnection(audioInput, 0, peak_L, 0);
    patchRMSLeft = new AudioConnection(audioInput, 0, rms_L, 0);
    patchFFTLeft = new AudioConnection(audioInput, 0, fft_L, 0);
    patchFilterLeft = new AudioConnection(audioInput, 0, filter_L, 0);
    patchRMSLowLeft = new AudioConnection(filter_L, 0, rmsLow_L, 0);

    patchMixerUnfilteredLeft = new AudioConnection(audioInput, 0, mixerUnfiltered, 0);
    patchMixerFilteredLeft = new AudioConnection(filter_L, mixerFiltered);

    patchPeakRight = new AudioConnection(audioInput, 1, peak_R, 0);
    patchRMSRight = new AudioConnection(audioInput, 1, rms_R, 0);
    patchFFTRight = new AudioConnection(audioInput, 1, fft_R, 0);
    patchFilterRight = new AudioConnection(audioInput, 1, filter_R, 0);
    patchRMSLowRight = new AudioConnection(filter_R, 0, rmsLow_R, 0);
    
    patchMixerUnfilteredRight = new AudioConnection(audioInput, 1, mixerUnfiltered, 1);
    patchMixerFilteredRight = new AudioConnection(filter_R, mixerFiltered);

    patchPeakMono = new AudioConnection(mixerUnfiltered, peak_M);
    patchRMSMono = new AudioConnection(mixerUnfiltered, rms_M);
    patchFFTMono = new AudioConnection(mixerUnfiltered, fft_M);
    patchRMSLowMono = new AudioConnection(mixerFiltered, rmsLow_M);

    audioShield = new AudioControlSGTL5000();
    
    mixerUnfiltered.gain(0, 0.5);
    mixerUnfiltered.gain(1, 0.5);
    mixerFiltered.gain(0, 0.5);
    mixerFiltered.gain(1, 0.5);

    // Butterworth filter, 12 db/octave
    // filter_L.setLowpass(0, LOWPASS_FREQUENCY);
    // filter_R.setLowpass(0, LOWPASS_FREQUENCY);

    // Linkwitz-Riley filter, 48 dB/octave
    filter_L.setLowpass(0, LOWPASS_FREQUENCY, 0.54);
    filter_L.setLowpass(1, LOWPASS_FREQUENCY, 1.3);
    filter_L.setLowpass(2, LOWPASS_FREQUENCY, 0.54);
    filter_L.setLowpass(3, LOWPASS_FREQUENCY, 1.3);
    filter_R.setLowpass(0, LOWPASS_FREQUENCY, 0.54);
    filter_R.setLowpass(1, LOWPASS_FREQUENCY, 1.3);
    filter_R.setLowpass(2, LOWPASS_FREQUENCY, 0.54);
    filter_R.setLowpass(3, LOWPASS_FREQUENCY, 1.3);

}

void AudioSensor::setup() {
    AudioMemory(MAX_MEMORY_BLOCKS);
    audioShield->enable();
    audioShield->volume(0);
    setLineInput();
    fft_L.windowFunction(AudioWindowHanning1024);
    fft_R.windowFunction(AudioWindowHanning1024);
    fft_M.windowFunction(AudioWindowHanning1024);
}

void AudioSensor::loop() {
    left->loop(&peak_L, &rms_L, &rmsLow_L, &fft_L);
    right->loop(&peak_R, &rms_R, &rmsLow_R, &fft_R);
    mono->loop(&peak_M, &rms_M, &rmsLow_M, &fft_M);
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

void AudioSensor::printStats() {
    Serial.print("AudioMemoryUsage: ");
    Serial.print(AudioMemoryUsage());
    Serial.print(", AudioMemoryUsageMax: ");
    Serial.print(AudioMemoryUsageMax());
    Serial.print(", AudioProcessorUsage: ");
    Serial.print(AudioProcessorUsage());
    Serial.print(", AudioProcessorUsageMax: ");
    Serial.print(AudioProcessorUsageMax());
    Serial.println();
}
