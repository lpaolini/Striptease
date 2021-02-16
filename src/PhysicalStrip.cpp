#include "PhysicalStrip.h"

PhysicalStrip::PhysicalStrip(CRGBSet &leds, uint16_t density) : StatefulStrip(leds, density) {}

PhysicalStrip::PhysicalStrip(CRGBSet *leds, uint16_t density) : StatefulStrip(leds, density) {}

PhysicalStrip::PhysicalStrip() {}

Strip *PhysicalStrip::buffered() {
    return new BufferedStrip(this);
}
