#ifndef BufferedStrip_h
#define BufferedStrip_h

#include "Strip.h"
#include "PhysicalStrip.h"

class BufferedStrip : public PhysicalStrip {
    private:
        CRGBSet *leds;
        Strip *strip;

    public:
        BufferedStrip(Strip *strip);
        void flush();
};

#endif
