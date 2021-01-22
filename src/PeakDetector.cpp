#include "PeakDetector.h"

PeakDetector::PeakDetector(unsigned int bufferSize, float peakFactor, float peakInfluence, unsigned int peakInhibit, float peakThreshold) {
    this->bufferSize = bufferSize;
    this->peakFactor = peakFactor;
    this->peakInfluence = peakInfluence;
    this->peakInhibit = peakInhibit;
    this->peakThreshold = peakThreshold;
    this->buffer = new float[bufferSize];
    this->skip = bufferSize;
    this->ptr = 0;
}

PeakDetector::~PeakDetector() {
    delete[] buffer;
}

float PeakDetector::avg() {
    float sum = 0;
    for (uint16_t i = 0; i < bufferSize; i++) {
        sum += buffer[i];
    }
    return sum / bufferSize;
}

float PeakDetector::stdDev(float mean) {
    float sum = 0;
    for (uint16_t i = 0; i < bufferSize; i++) {
        sum += pow(buffer[i] - mean, 2);
    }
    return sqrtf(sum / bufferSize);
}

bool PeakDetector::isPeak(float value) {
    bool peakDetected = false;
    if (skip > 0) {
        buffer[ptr] = value;
    } else {
        float mean = avg();
        float peak = abs(value - mean);
        peakDetected = peak > peakThreshold && peak > peakFactor * stdDev(mean);
        if (peakDetected) {
            float prevValue = buffer[(ptr + bufferSize - 1) % bufferSize];
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
