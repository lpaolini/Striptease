#ifndef Interval_h
#define Interval_h

class Interval {
    private:
        elapsedMicros timeMicroseconds = 0;

    public:
        void reset() {
            timeMicroseconds = 0;
        }

        double time(double interval) {
            double intervalMicroseconds = interval * 65536000;
            while (timeMicroseconds >= intervalMicroseconds) {
                timeMicroseconds -= intervalMicroseconds;
            }
            return double(timeMicroseconds) / double(intervalMicroseconds);
        }

        double time(double stdInterval, double cursor) {
            return time(stdInterval / 3, stdInterval * 3, cursor);
        }

        double time(double minInterval, double maxInterval, double cursor) {
            return time(minInterval + (maxInterval - minInterval) * (1 - cursor));
        }
};

#endif
