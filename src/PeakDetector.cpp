#include "PeakDetector.h"

PeakDetector::PeakDetector(unsigned int bufferSize, double peakFactor, double peakInfluence, unsigned int peakInhibit, double peakThreshold) {
    this->bufferSize = bufferSize;
    this->peakFactor = peakFactor;
    this->peakInfluence = peakInfluence;
    this->peakInhibit = peakInhibit;
    this->peakThreshold = peakThreshold;
    this->buffer = new double[bufferSize];
    this->skip = bufferSize;
    this->ptr = 0;
}

PeakDetector::~PeakDetector() {
    delete[] buffer;
}

double PeakDetector::avg() {
    double sum = 0;
    for (uint16_t i = 0; i < bufferSize; i++) {
        sum += buffer[i];
    }
    return sum / bufferSize;
}

double PeakDetector::stdDev(double mean) {
    double sum = 0;
    for (uint16_t i = 0; i < bufferSize; i++) {
        sum += pow(buffer[i] - mean, 2);
    }
    return sqrtf(sum / bufferSize);
}

bool PeakDetector::isPeak(double value) {
    bool peakDetected = false;
    if (skip > 0) {
        buffer[ptr] = value;
    } else {
        double mean = avg();
        double peak = abs(value - mean);
        peakDetected = peak > peakThreshold && peak > peakFactor * stdDev(mean);
        if (peakDetected) {
            double prevValue = buffer[(ptr + bufferSize - 1) % bufferSize];
            buffer[ptr] = value * peakInfluence + prevValue * (1 - peakInfluence);
        } else {
            buffer[ptr] = value;
        }
    }

    ptr = (ptr + 1) % bufferSize;
    skip = skip > 0 ? skip - 1 : 0;

    if (peakDetected && (millis() - lastPeak > peakInhibit)) {
        lastPeak = millis();
        return true;
    } else {
        return false;
    }
}
