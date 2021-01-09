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
        AudioInputI2S audioInput;
        AudioAnalyzePeak peak_L;
        AudioAnalyzeRMS rms_L;
        AudioAnalyzeFFT256 fft_L;
        AudioAnalyzePeak peak_R;
        AudioAnalyzeRMS rms_R;
        AudioAnalyzeFFT256 fft_R;
        AudioMixer4 mixer;
        AudioAnalyzePeak peak_M;
        AudioAnalyzeRMS rms_M;
        AudioConnection *cpl;
        AudioConnection *crl;
        AudioConnection *cfl;
        AudioConnection *cml;
        AudioConnection *cpr;
        AudioConnection *crr;
        AudioConnection *cfr;
        AudioConnection *cmr;
        AudioConnection *cpm;
        AudioConnection *crm;
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
};

#endif
