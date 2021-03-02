#include "AudioChannel.h"

AudioChannel::AudioChannel() {
    beatDetector = new PeakDetector(BUFFER_SIZE, PEAK_FACTOR, PEAK_INFLUENCE, PEAK_INHIBIT_MS, PEAK_THRESHOLD);
    for (uint16_t i = 0; i < FFT_BANDS; i++) {
        beatDetectors[i] = new PeakDetector(BUFFER_SIZE, 2.5f, PEAK_INFLUENCE, PEAK_INHIBIT_MS, 0.25f);
    }
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
    beatDetected = beatDetector->isPeak(value);
}

void AudioChannel::setBand(AudioAnalyzeFFT1024 *fft, uint8_t band, uint16_t fromBin, uint16_t toBin) {
    bands[band].peak = 20 * log10(max(1e-5, fft->read(fromBin, toBin)));
}

void AudioChannel::feedBins(AudioAnalyzeFFT1024 *fft) {
    for (uint16_t i = 0; i < FFT_BINS; i++) {
        fftBin[i] = fft->read(i);
    }
}

void AudioChannel::feedBands(AudioAnalyzeFFT1024 *fft) {
    // 16 band
    setBand(fft, 0, 0, 0);
    setBand(fft, 1, 1, 1);
    setBand(fft, 2, 2, 3);
    setBand(fft, 3, 4, 6);
    setBand(fft, 4, 7, 10);
    setBand(fft, 5, 11, 15);
    setBand(fft, 6, 16, 22);
    setBand(fft, 7, 23, 32);
    setBand(fft, 8, 33, 46);
    setBand(fft, 9, 47, 66);
    setBand(fft, 10, 67, 93);
    setBand(fft, 11, 94, 131);
    setBand(fft, 12, 132, 184);
    setBand(fft, 13, 185, 257);
    setBand(fft, 14, 258, 359);
    setBand(fft, 15, 360, 511);
}

void AudioChannel::loop(AudioAnalyzePeak *peak, AudioAnalyzeRMS *rms, AudioAnalyzeRMS *rmsLow, AudioAnalyzeFFT1024 *fft) {
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
        feedBins(fft);
        feedBands(fft);

        float peakBandValue = -60;
        dominantBand = 0;
        for (uint8_t i = 0; i < FFT_BANDS; i++) {
            bands[i].peakSmooth = max(bands[i].peakSmooth, bands[i].peak);
            if (bands[i].peak > peakBandValue) {
                peakBandValue = bands[i].peak;
                dominantBand = i;
            }
            bands[i].beatDetected = beatDetectors[i]->isPeak(bands[i].peak);
        }

    }
    if (peakFadeTimer.isElapsed()) {
        peakSmooth *= .990;
        peakHold *= .999;
        for (uint8_t i = 0; i < FFT_BANDS; i++) {
            bands[i].peakSmooth = ((bands[i].peakSmooth + 60) * .990 - 60);
            bands[i].peakHold = ((bands[i].peakHold + 60) * .999 - 60);
        }
    }
}
