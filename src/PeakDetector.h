#ifndef PeakDetector_h
#define PeakDetector_h

#include <Arduino.h>
#include <Audio.h>
#include <FastLED.h>

class PeakDetector {
    private:
        unsigned int bufferSize;
        float peakFactor;
        float peakInfluence;
        unsigned int peakInhibit;
        float peakThreshold;
        unsigned int skip;
        unsigned int ptr;
        float *buffer;
        float avg();
        float stdDev(float mean);
        unsigned long lastPeak;

    public:
        PeakDetector(unsigned int bufferSize, float peakFactor, float peakInfluence, unsigned int peakInhibit, float peakThreshold);
        ~PeakDetector();
        bool isPeak(float value);
};

#endif
