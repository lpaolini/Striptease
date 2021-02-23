#ifndef PhysicalStrip_h
#define PhysicalStrip_h

#include "Strip.h"
#include "strip/BufferedStrip.h"
#include "strip/StatefulStrip.h"

class PhysicalStrip : public StatefulStrip {
    public:
        PhysicalStrip(CRGBSet &leds, uint16_t density = 0);
        Strip *buffered();
};

#endif
