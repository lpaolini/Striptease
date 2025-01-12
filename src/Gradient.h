#ifndef Palette_h
#define Palette_h

#include <vector>
#include <FastLED.h>

class Gradient {
    private:
        std::vector<CRGB> colors;

        static CRGB interpolate(CRGB &c1, CRGB &c2, double fraction) {
            return CRGB(
                c1.r + (c2.r - c1.r) * fraction,
                c1.g + (c2.g - c1.g) * fraction,
                c1.b + (c2.b - c1.b) * fraction
            );
        }

        CRGB getInterpolatedColor(uint8_t segments, double fraction) {
            uint8_t segment = floor(fraction * segments);
            double segmentFraction = fraction * segments - segment;
            return interpolate(colors.at(segment), colors.at(segment + 1), segmentFraction);
        }

        void addColors() {}

        template <class CRGB, class... Rest>
        void addColors(CRGB color, Rest... rest) {
            colors.push_back(color);
            addColors(rest...);
        }

    public:
        template <class... CRGB>
        Gradient(CRGB... colors) {
            addColors(colors...);
        }

        CRGB getColor(double fraction) {
            if (colors.size()) {
                uint8_t segments = colors.size() - 1;
                if (segments > 0) {
                    if (fraction <= 0) return colors.at(0);
                    if (fraction >= 1) return colors.at(segments);
                    return getInterpolatedColor(segments, fraction);
                }
                return colors.at(segments);
            }
            return CRGB::Black;
        }

        CRGB getRandomColor(uint16_t maxColors = UINT16_MAX) {
            return getColor((double) (rand() % maxColors) / (maxColors - 1));
        }
};

#endif
