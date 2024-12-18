#include "PhysicalStrip.h"

PhysicalStrip::PhysicalStrip(CRGBSet &leds, uint16_t density) : StatefulStrip(leds, density) {}

Strip *PhysicalStrip::buffered(uint8_t opacity) {
    return new BufferedStrip(this, opacity);
}
