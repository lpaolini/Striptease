#ifndef PhysicalStrip_h
#define PhysicalStrip_h

#include "Strip.h"
#include "BufferedStrip.h"
#include "StatefulStrip.h"

class PhysicalStrip : public StatefulStrip {
    public:
        PhysicalStrip(CRGBSet &leds, uint16_t density = 0);
        Strip *buffered();
};

#endif
