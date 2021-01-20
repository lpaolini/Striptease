#ifndef Point_h
#define Point_h

#include <Arduino.h>

class Point {
    public:
        float x;
        float y;
        static Point fromPolar(float radius, float angle) {
            return Point(
                radius * cosf(angle),
                radius * sinf(angle)
            );
        };
        Point() {};
        Point(float x, float y) {
            this->x = x;
            this->y = y;
        }
        float radius() {
            return sqrt(pow(x, 2) + pow(y, 2));
        }
        float angle() {
            return x == 0 && y == 0 ? 0 : atan2(y, x);
        }
        Point& set(float x, float y) {
            this->x = x;
            this->y = y;
            return *this;
        }
        Point& translate(Point p) {
            return translate(p.x, p.y);
        }
        Point& translate(float tx, float ty) {
            return set(x - tx, y - ty);
        }
        Point& rotate(float theta) {
            float cosTheta = cos(theta);
            float sinTheta = sin(theta);
            return set(
                x * cosTheta - y * sinTheta,
                x * sinTheta + y * cosTheta
            );
        }
};

#endif
