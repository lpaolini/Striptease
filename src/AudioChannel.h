#ifndef AudioChannel_h
#define AudioChannel_h

#include <Arduino.h>
#include <Audio.h>
#include <FastLED.h>
#include "PeakDetector.h"
#include "Timer.h"

class AudioChannel {
    private:
        static const int BUFFER_SIZE = 256; // 2.9ms * 256 ~= 0.74s
        static const int FFT_BINS = 512;
        static const int FFT_BANDS = 16;
        static const int SIGNAL_HOLD_MS = 10000;
        static constexpr float SIGNAL_THRESHOLD = .01f;
        static constexpr float PEAK_FACTOR = 2.2f;
        static constexpr float PEAK_INFLUENCE = 0.5f;
        static constexpr float PEAK_THRESHOLD = .05f;
        static const int PEAK_INHIBIT_MS = 100;
        static constexpr float CLIPPING_THRESHOLD = .99f;
        unsigned long lastSignal = 0;
        PeakDetector beatDetector = PeakDetector(BUFFER_SIZE, PEAK_FACTOR, PEAK_INFLUENCE, PEAK_INHIBIT_MS, PEAK_THRESHOLD);
        void feedPeak(float value);
        void feedRMS(float value);
        void feedRMSLow(float value);
        void detectSignal(float value);
        void detectBeat(float value);
        void setBand(AudioAnalyzeFFT1024 *fft, uint8_t band, uint16_t fromBin, uint16_t toBin);
        Timer peakFadeTimer = Timer(10);

    public:
        float rms = 0;
        float rmsLow = 0;
        float peak = 0;
        float peakSmooth = 0;
        float peakHold = 0;
        bool signalDetected = false;
        bool beatDetected = false;
        bool clipping = false;
        float fftBin[FFT_BINS];
        float fftBands[FFT_BANDS];
        float fftBandsSmooth[FFT_BANDS];
        uint16_t dominantBand;

        AudioChannel();
        void loop(AudioAnalyzePeak *peak = nullptr, AudioAnalyzeRMS *rms = nullptr, AudioAnalyzeRMS *rmsLow = nullptr, AudioAnalyzeFFT1024 *fft = nullptr);
};

#endif
