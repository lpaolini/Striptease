#ifndef BufferedStrip_h
#define BufferedStrip_h

#include "Strip.h"
#include "strip/StatefulStrip.h"

class BufferedStrip : public StatefulStrip {
    private:
        CRGBSet *leds;
        Strip *strip;

    public:
        BufferedStrip(Strip *strip);
        void flush() override;
};

#endif
