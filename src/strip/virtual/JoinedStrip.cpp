#include "JoinedStrip.h"

JoinedStrip::JoinedStrip(Strip *strip1, Strip *strip2, int16_t gap) {
    this->strip1 = strip1;
    this->strip2 = strip2;
    this->gap = max(0, gap);
    CRGB *buffer = new CRGB[this->gap];
    CRGBSet *bufferSet = new CRGBSet(buffer, this->gap);
    gapStrip = new StatefulStrip(bufferSet);
}

Strip *JoinedStrip::overlay(double opacity) {
    return new BufferedStrip(this, opacity);
}

uint16_t JoinedStrip::size() {
    return strip1->size() + gapStrip->size() + strip2->size();
}

bool JoinedStrip::isInStrip1(int16_t index) {
    return strip1->isInRange(toStrip1(index));
}

bool JoinedStrip::isInGap(int16_t index) {
    return gapStrip->isInRange(toGap(index));
}

bool JoinedStrip::isInStrip2(int16_t index) {
    return strip2->isInRange(toStrip2(index));
}

int16_t JoinedStrip::toStrip1(int16_t index) {
    return index;
}

int16_t JoinedStrip::toGap(int16_t index) {
    return index - strip1->size();
}

int16_t JoinedStrip::toStrip2(int16_t index) {
    return index - strip1->size() - gapStrip->size();
}

double JoinedStrip::relativeGradient(int16_t indexFrom, int16_t indexTo, int16_t p, double gradientFrom, double gradientTo) {
    return gradientFrom + (gradientTo - gradientFrom) * p / (indexTo - indexFrom);
}

void JoinedStrip::_fade(int16_t indexFrom, int16_t indexTo, uint8_t amount) {
    if (crop(indexFrom, indexTo)) {
        if (isInStrip1(indexFrom)) {
            if (isInStrip1(indexTo)) {
                strip1->fade(amount, toStrip1(indexFrom), toStrip1(indexTo));
            } else if (isInGap(indexTo)) {
                strip1->fade(amount, toStrip1(indexFrom), strip1->last());
                gapStrip->fade(amount, gapStrip->first(), toGap(indexTo));
            } else if (isInStrip2(indexTo)) {
                strip1->fade(amount, toStrip1(indexFrom), strip1->last());
                gapStrip->Strip::fade(amount);
                strip2->fade(amount, strip2->first(), toStrip2(indexTo));
            }
        } else if (isInGap(indexFrom)) {
            if (isInGap(indexTo)) {
                gapStrip->fade(amount, toGap(indexFrom), toGap(indexTo));
            } else if (isInStrip2(indexTo)) {
                gapStrip->fade(amount, toGap(indexFrom), gapStrip->last());
                strip2->fade(amount, strip2->first(), toStrip2(indexTo));
            }
        } else if (isInStrip2(indexFrom)) {
            strip2->fade(amount, toStrip2(indexFrom), toStrip2(indexTo));
        }
    }
}

void JoinedStrip::_blur(int16_t indexFrom, int16_t indexTo, uint8_t amount) {
    if (crop(indexFrom, indexTo)) {
        if (isInStrip1(indexFrom)) {
            if (isInStrip1(indexTo)) {
                strip1->blur(amount, toStrip1(indexFrom), toStrip1(indexTo));
            } else if (isInGap(indexTo)) {
                strip1->blur(amount, toStrip1(indexFrom), strip1->last());
                gapStrip->blur(amount, gapStrip->first(), toGap(indexTo));
            } else if (isInStrip2(indexTo)) {
                strip1->blur(amount, toStrip1(indexFrom), strip1->last());
                gapStrip->Strip::blur(amount);
                strip2->blur(amount, strip2->first(), toStrip2(indexTo));
            }
        } else if (isInGap(indexFrom)) {
            if (isInGap(indexTo)) {
                gapStrip->blur(amount, toGap(indexFrom), toGap(indexTo));
            } else if (isInStrip2(indexTo)) {
                gapStrip->blur(amount, toGap(indexFrom), gapStrip->last());
                strip2->blur(amount, strip2->first(), toStrip2(indexTo));
            }
        } else if (isInStrip2(indexFrom)) {
            strip2->blur(amount, toStrip2(indexFrom), toStrip2(indexTo));
        }
    }
}

CRGB JoinedStrip::_shiftUp(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        if (isInStrip1(indexFrom)) {
            if (isInStrip1(indexTo)) {
                return strip1->shiftUp(toStrip1(indexFrom), toStrip1(indexTo), in);
            } else if (isInGap(indexTo)) {
                CRGB fromStrip1 = strip1->shiftUp(toStrip1(indexFrom), strip1->last(), in);
                return gapStrip->shiftUp(gapStrip->first(), toGap(indexTo), fromStrip1);
            } else if (isInStrip2(indexTo)) {
                CRGB fromStrip1 = strip1->shiftUp(toStrip1(indexFrom), strip1->last(), in);
                CRGB fromGap = gapStrip->Strip::shiftUp(fromStrip1);
                return strip2->shiftUp(strip2->first(), toStrip2(indexTo), fromGap);
            }
        } else if (isInGap(indexFrom)) {
            if (isInGap(indexTo)) {
                return gapStrip->shiftUp(toGap(indexFrom), toGap(indexTo), in);
            } else if (isInStrip2(indexTo)) {
                CRGB fromGap = gapStrip->shiftUp(toGap(indexFrom), gapStrip->last(), in);
                return strip2->shiftUp(strip2->first(), toStrip2(indexTo), fromGap);
            }
        } else if (isInStrip2(indexFrom)) {
            return strip2->shiftUp(toStrip2(indexFrom), toStrip2(indexTo), in);
        }
    }
    return CRGB::Black;
}

CRGB JoinedStrip::_shiftDown(int16_t indexFrom, int16_t indexTo, CRGB in) {
    if (crop(indexFrom, indexTo)) {
        if (isInStrip1(indexFrom)) {
            if (isInStrip1(indexTo)) {
                return strip1->shiftDown(toStrip1(indexFrom), toStrip1(indexTo), in);
            } else if (isInGap(indexTo)) {
                CRGB fromGap = gapStrip->shiftDown(gapStrip->first(), toGap(indexTo), in);
                return strip1->shiftDown(toStrip1(indexFrom), strip1->last(), fromGap);
            } else if (isInStrip2(indexTo)) {
                CRGB fromStrip2 = strip2->shiftDown(strip2->first(), toStrip2(indexTo), in);
                CRGB fromGap = gapStrip->Strip::shiftDown(fromStrip2);
                return strip1->shiftDown(toStrip1(indexFrom), strip1->last(), fromGap);
            }
        } else if (isInGap(indexFrom)) {
            if (isInGap(indexTo)) {
                return gapStrip->shiftDown(toGap(indexFrom), toGap(indexTo), in);
            } else if (isInStrip2(indexTo)) {
                CRGB fromStrip2 = strip2->shiftDown(strip2->first(), toStrip2(indexTo), in);
                return gapStrip->shiftDown(toGap(indexFrom), gapStrip->last(), fromStrip2);
            }
        } else if (isInStrip2(indexFrom)) {
            return strip2->shiftDown(toStrip2(indexFrom), toStrip2(indexTo), in);
        }
    }
    return CRGB::Black;
}

bool JoinedStrip::_paintSolid(int16_t indexFrom, int16_t indexTo, CRGB color, bool add) {
    if (crop(indexFrom, indexTo)) {
        if (isInStrip1(indexFrom)) {
            if (isInStrip1(indexTo)) {
                return strip1->paint(toStrip1(indexFrom), toStrip1(indexTo), color, add);
            } else if (isInGap(indexTo)) {
                bool s1 = strip1->paint(toStrip1(indexFrom), strip1->last(), color, add);
                bool sg = gapStrip->paint(gapStrip->first(), toGap(indexTo), color, add);
                return s1 || sg;
            } else if (isInStrip2(indexTo)) {
                bool s1 = strip1->paint(toStrip1(indexFrom), strip1->last(), color, add);
                gapStrip->Strip::paint(color, add);
                bool s2 = strip2->paint(strip2->first(), toStrip2(indexTo), color, add);
                return s1 || s2;
            }
        } else if (isInGap(indexFrom)) {
            if (isInGap(indexTo)) {
                return gapStrip->paint(toGap(indexFrom), toGap(indexTo), color, add);
            } else if (isInStrip2(indexTo)) {
                bool sg = gapStrip->paint(toGap(indexFrom), gapStrip->last(), color, add);
                bool s2 = strip2->paint(strip2->first(), toStrip2(indexTo), color, add);
                return sg || s2;
            }
        } else if (isInStrip2(indexFrom)) {
            return strip2->paint(toStrip2(indexFrom), toStrip2(indexTo), color, add);
        }
    }
    return false;
}

bool JoinedStrip::_paintGradient(int16_t indexFrom, int16_t indexTo, Gradient *gradient, double gradientFrom, double gradientTo, bool add) {
    if (crop(indexFrom, indexTo)) {
        if (isInStrip1(indexFrom)) {
            if (isInStrip1(indexTo)) {
                return strip1->paint(toStrip1(indexFrom), toStrip1(indexTo), gradient, 0, 1, add);
            } else if (isInGap(indexTo)) {
                uint16_t p1 = strip1->size() - toStrip1(indexFrom);
                bool s1 = strip1->paint(toStrip1(indexFrom), strip1->last(), gradient, 0, relativeGradient(indexFrom, indexTo, p1, gradientFrom, gradientTo), add);
                bool sg = gapStrip->paint(gapStrip->first(), toGap(indexTo), gradient, relativeGradient(indexFrom, indexTo, p1 + 1, gradientFrom, gradientTo), 1, add);
                return s1 || sg;
            } else if (isInStrip2(indexTo)) {
                uint16_t p1 = strip1->size() - toStrip1(indexFrom);
                uint16_t p2 = p1 + gap;
                bool s1 = strip1->paint(toStrip1(indexFrom), strip1->last(), gradient, 0, relativeGradient(indexFrom, indexTo, p1, gradientFrom, gradientTo), add);
                gapStrip->Strip::paint(gradient, relativeGradient(indexFrom, indexTo, p1 + 1, gradientFrom, gradientTo), relativeGradient(indexFrom, indexTo, p2, gradientFrom, gradientTo), add);
                bool s2 = strip2->paint(strip2->first(), toStrip2(indexTo), gradient, relativeGradient(indexFrom, indexTo, p2 + 1, gradientFrom, gradientTo), 1, add);
                return s1 || s2;
            }
        } else if (isInGap(indexFrom)) {
            if (isInGap(indexTo)) {
                return gapStrip->paint(toGap(indexFrom), toGap(indexTo), gradient, 0, 1, add);
            } else if (isInStrip2(indexTo)) {
                uint16_t p2 = gap - toGap(indexFrom);
                bool sg = gapStrip->paint(toGap(indexFrom), gapStrip->last(), gradient, 0, relativeGradient(indexFrom, indexTo, p2, gradientFrom, gradientTo), add);
                bool s2 = strip2->paint(strip2->first(), toStrip2(indexTo), gradient, relativeGradient(indexFrom, indexTo, p2 + 1, gradientFrom, gradientTo), 1, add);
                return sg || s2;
            }
        } else if (isInStrip2(indexFrom)) {
            return strip2->paint(toStrip2(indexFrom), toStrip2(indexTo), gradient, 0, 1, add);
        }
    }
    return false;
}

bool JoinedStrip::_paintRainbow(int16_t indexFrom, int16_t indexTo, uint8_t initialHue, uint8_t deltaHue) {
    if (crop(indexFrom, indexTo)) {
        if (isInStrip1(indexFrom)) {
            if (isInStrip1(indexTo)) {
                return strip1->rainbow(initialHue, deltaHue, toStrip1(indexFrom), toStrip1(indexTo));
            } else if (isInGap(indexTo)) {
                bool s1 = strip1->rainbow(initialHue, deltaHue, toStrip1(indexFrom), strip1->last());
                bool sg = gapStrip->rainbow(initialHue + deltaHue * (strip1->size() - indexFrom), deltaHue, gapStrip->first(), toGap(indexTo));
                return s1 || sg;
            } else if (isInStrip2(indexTo)) {
                bool s1 = strip1->rainbow(initialHue, deltaHue, toStrip1(indexFrom), strip1->last());
                gapStrip->Strip::rainbow(initialHue + deltaHue * (strip1->size() - indexFrom), deltaHue);
                bool s2 = strip2->rainbow(initialHue + deltaHue * (strip1->size() + gap - indexFrom), deltaHue, strip2->first(), toStrip2(indexTo));
                return s1 || s2;
            }
        } else if (isInGap(indexFrom)) {
            if (isInGap(indexTo)) {
                return gapStrip->rainbow(initialHue, deltaHue, toGap(indexFrom), toGap(indexTo));
            } else if (isInStrip2(indexTo)) {
                bool sg = gapStrip->rainbow(initialHue, deltaHue, toGap(indexFrom), gapStrip->last());
                bool s2 = strip2->rainbow(initialHue + deltaHue * (strip1->size() + gap - indexFrom), deltaHue, strip2->first(), toStrip2(indexTo));
                return sg || s2;
            }
        } else if (isInStrip2(indexFrom)) {
            return strip2->rainbow(initialHue, deltaHue, toStrip2(indexFrom), toStrip2(indexTo));
        }
    }
    return false;
}

bool JoinedStrip::paintNormalizedSize(double positionFrom, int16_t size, CRGB color, bool add) {
    uint16_t indexFrom = fromNormalizedPosition(positionFrom, size);
    uint16_t indexTo = indexFrom + size - 1;
    return paint(indexFrom, indexTo, color, add);
}

CRGB JoinedStrip::getIndex(int16_t index) {
    if (isInStrip1(index)) {
        return strip1->getIndex(toStrip1(index));
    } else if (isInGap(index)) {
        return gapStrip->getIndex(toGap(index));
    } else if (isInStrip2(index)) {
        return strip2->getIndex(toStrip2(index));
    }
    return CRGB::Black;
}
