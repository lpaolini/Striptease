#include "PhysicalStrip.h"

PhysicalStrip::PhysicalStrip(CRGBSet &leds, uint16_t density) : StatefulStrip(leds, density) {}

Strip *PhysicalStrip::buffered() {
    return new BufferedStrip(this);
}
