#ifndef AudioChannel_h
#define AudioChannel_h

#include <Arduino.h>
#include <Audio.h>
#include "PeakDetector.h"
#include "Timer.h"

class AudioChannel {
    private:
        static const int BUFFER_SIZE = 256; // 2.9ms * 256 ~= 0.74s
        static const int FFT_BINS = 512;
        static const int FFT_BANDS = 16;
        static const int SIGNAL_HOLD_MS = 10000;
        static constexpr double SIGNAL_THRESHOLD = .01f;
        static constexpr double PEAK_FACTOR = 2.2f;
        static constexpr double PEAK_INFLUENCE = 0.5f;
        static constexpr double PEAK_THRESHOLD = .05f;
        static const int PEAK_INHIBIT_MS = 100;
        static constexpr double CLIPPING_THRESHOLD = .99f;
        unsigned long lastSignal = 0;
        PeakDetector *beatDetector;
        PeakDetector *peakDetectors[FFT_BANDS];
        void feedPeak(double value);
        void feedRMS(double value);
        void feedRMSLow(double value);
        void feedBins(AudioAnalyzeFFT1024 *fft);
        void feedBands(AudioAnalyzeFFT1024 *fft);
        void detectSignal(double value);
        void detectBeat(double value);
        void setBand(AudioAnalyzeFFT1024 *fft, uint8_t band, uint16_t fromBin, uint16_t toBin);
        Timer peakFadeTimer = Timer(10);

    public:
        struct Band {
            double peak = 0;
            double peakSmooth = 0;
            double peakHold = 0;
            // bool signalDetected = false;
            bool peakDetected = false;
            // bool clipping = false;
        };
        double rms = 0;
        double rmsLow = 0;
        double peak = 0;
        double peakSmooth = 0;
        double peakHold = 0;
        bool signalDetected = false;
        bool beatDetected = false;
        bool clipping = false;
        double fftBin[FFT_BINS];
        Band bands[FFT_BANDS];
        uint16_t dominantBand;

        AudioChannel();
        void loop(AudioAnalyzePeak *peak = nullptr, AudioAnalyzeRMS *rms = nullptr, AudioAnalyzeRMS *rmsLow = nullptr, AudioAnalyzeFFT1024 *fft = nullptr);
};

#endif
