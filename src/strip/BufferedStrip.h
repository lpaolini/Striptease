#ifndef BufferedStrip_h
#define BufferedStrip_h

#include "Strip.h"
#include "strip/StatefulStrip.h"

class BufferedStrip : public StatefulStrip {
    private:
        CRGBSet *leds;
        Strip *strip;
        uint8_t opacity;

    public:
        BufferedStrip(Strip *strip, uint8_t opacity);
        void flush() override;
};

#endif
