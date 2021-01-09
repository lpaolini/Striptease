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
}

void AudioChannel::loop(AudioAnalyzePeak *peak, AudioAnalyzeRMS *rms, AudioAnalyzeFFT256 *fft) {
    if (peak != nullptr && peak->available()) {
        feedPeak(peak->read());
    }
    if (rms != nullptr && rms->available()) {
        feedRMS(rms->read());
    }
    if (fft != nullptr && fft->available()) {
        for (int i = 0; i < 40; i++) {
            fftBin[i] = fft->read(i);
        }
    }
    if (peakFadeTimer.isElapsed()) {
        peakSmooth *= .990;
        peakHold *= .999;
    }
}
