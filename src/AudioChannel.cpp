#include "AudioChannel.h"

AudioChannel::AudioChannel() {
    peakFadeTimer.reset();
}

void AudioChannel::feedPeak(float value) {
    peak = value;
    peakSmooth = max(peakSmooth, value);
    peakHold = max(peakHold, value);
    clipping = value > CLIPPING_THRESHOLD;
}

void AudioChannel::feedRMS(float value) {
    rms = value;
    detectSignal(value);
}

void AudioChannel::feedRMSLow(float value) {
    rmsLow = value;
    detectBeat(value);
}

void AudioChannel::detectSignal(float value) {
    if (millis() - lastSignal > SIGNAL_HOLD_MS) {
        signalDetected = false;
    }
    if (value > SIGNAL_THRESHOLD) {
        signalDetected = true;
        lastSignal = millis();
    }
}

void AudioChannel::detectBeat(float value) {
    beatDetected = beatDetector.isPeak(value);
    beatWasDetected = beatWasDetected || beatDetected;
}

void AudioChannel::loop(AudioAnalyzePeak *peak, AudioAnalyzeRMS *rms, AudioAnalyzeRMS *rmsLow, AudioAnalyzeFFT256 *fft) {
    if (peak != nullptr && peak->available()) {
        feedPeak(peak->read());
    }
    if (rms != nullptr && rms->available()) {
        feedRMS(rms->read());
    }
    if (rmsLow != nullptr && rmsLow->available()) {
        feedRMSLow(rmsLow->read());
    }
    if (fft != nullptr && fft->available()) {
        for (int i = 0; i < FFT_BINS; i++) {
            fftBin[i] = fft->read(i);
        }
    }
    if (peakFadeTimer.isElapsed()) {
        peakSmooth *= .990;
        peakHold *= .999;
    }
}

// bool AudioChannel::trigger(uint8_t noSignalRandomness, uint8_t signalRandomness) {
//     return signalDetected
//         ? beatDetected || random8() < signalRandomness
//         : random8() < noSignalRandomness;
// }

void AudioChannel::resetTrigger() {
    beatWasDetected = false;
}

bool AudioChannel::trigger(uint8_t noSignalRandomness, uint8_t signalRandomness) {
    bool trigger = signalDetected
        ? beatWasDetected || random8() < signalRandomness
        : random8() < noSignalRandomness;
    resetTrigger();
    return trigger;
}
