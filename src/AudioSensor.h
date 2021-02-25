#ifndef AudioSensor_h
#define AudioSensor_h

#include <Arduino.h>
#include <Audio.h>
#include <FastLED.h>
#include "AudioChannel.h"

class AudioSensor {
    private:
        static const uint8_t DEFAULT_MIC_GAIN = 40;
        static const uint8_t DEFAULT_LINE_IN_LEVEL = 5;
        static const uint8_t MAX_MEMORY_BLOCKS = 30;
        static constexpr float LOWPASS_FREQUENCY = 250;

        AudioInputI2S audioInput;

        AudioAnalyzePeak peak_L;
        AudioAnalyzeRMS rms_L;
        AudioFilterBiquad filter_L;
        AudioAnalyzeRMS rmsLow_L;
        AudioAnalyzeFFT1024 fft_L;

        AudioAnalyzePeak peak_R;
        AudioAnalyzeRMS rms_R;
        AudioFilterBiquad filter_R;
        AudioAnalyzeRMS rmsLow_R;
        AudioAnalyzeFFT1024 fft_R;

        AudioMixer4 mixerUnfiltered;
        AudioMixer4 mixerFiltered;

        AudioAnalyzePeak peak_M;
        AudioAnalyzeRMS rms_M;
        AudioFilterBiquad filter_M;
        AudioAnalyzeRMS rmsLow_M;
        AudioAnalyzeFFT1024 fft_M;

        AudioConnection *patchPeakLeft;
        AudioConnection *patchRMSLeft;
        AudioConnection *patchFilterLeft;
        AudioConnection *patchRMSLowLeft;
        AudioConnection *patchFFTLeft;

        AudioConnection *patchMixerUnfilteredLeft;
        AudioConnection *patchMixerFilteredLeft;
        
        AudioConnection *patchPeakRight;
        AudioConnection *patchRMSRight;
        AudioConnection *patchFilterRight;
        AudioConnection *patchRMSLowRight;
        AudioConnection *patchFFTRight;

        AudioConnection *patchMixerUnfilteredRight;
        AudioConnection *patchMixerFilteredRight;

        AudioConnection *patchPeakMono;
        AudioConnection *patchRMSMono;
        AudioConnection *patchFilterMono;
        AudioConnection *patchRMSLowMono;
        AudioConnection *patchFFTMono;

        AudioControlSGTL5000 *audioShield;
        uint8_t micGain = DEFAULT_MIC_GAIN;
        uint8_t lineInLevel = DEFAULT_LINE_IN_LEVEL;

    public:
        AudioChannel *left = new AudioChannel();
        AudioChannel *right = new AudioChannel();
        AudioChannel *mono = new AudioChannel();
        AudioSensor();
        void setup();
        void loop();
        void setMicInput();
        void setLineInput();
        void setMicGain(uint8_t micGain);
        uint8_t getMicGain();
        void increaseMicGain();
        void decreaseMicGain();
        void setLineInLevel(uint8_t lineInLevel);
        uint8_t getLineInLevel();
        void increaseLineInLevel();
        void decreaseLineInLevel();
        float getNormalizedMicGain();
        float getNormalizedLineInLevel();
        void printStats();
};

#endif
