#ifndef PeakDetector_h
#define PeakDetector_h

#include <Arduino.h>

class PeakDetector {
    private:
        unsigned int bufferSize;
        double peakFactor;
        double peakInfluence;
        unsigned int peakInhibit;
        double peakThreshold;
        unsigned int skip;
        unsigned int ptr;
        double *buffer;
        double avg();
        double stdDev(double mean);
        unsigned long lastPeak;

    public:
        PeakDetector(unsigned int bufferSize, double peakFactor, double peakInfluence, unsigned int peakInhibit, double peakThreshold);
        ~PeakDetector();
        bool isPeak(double value);
};

#endif
