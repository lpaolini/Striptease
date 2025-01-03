#ifndef BufferedStrip_h
#define BufferedStrip_h

#include <FastLED.h>
#include "Strip.h"
#include "StatefulStrip.h"

class BufferedStrip : public StatefulStrip {
    private:
        CRGBSet *leds;
        Strip *strip;
        double opacity;

    public:
        BufferedStrip(Strip *strip, double opacity);
        void flush() override;
};

#endif
