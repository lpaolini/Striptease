#ifndef Point_h
#define Point_h

#include <Arduino.h>

class Point {
    public:
        double x;
        double y;
        static Point fromPolar(double radius, double angle) {
            return Point(
                radius * cosf(angle),
                radius * sinf(angle)
            );
        };
        Point() {};
        Point(double x, double y) {
            this->x = x;
            this->y = y;
        }
        double radius() {
            return sqrt(pow(x, 2) + pow(y, 2));
        }
        double angle() {
            return x == 0 && y == 0 ? 0 : atan2(y, x);
        }
        Point& set(double x, double y) {
            this->x = x;
            this->y = y;
            return *this;
        }
        Point& translate(Point p) {
            return translate(p.x, p.y);
        }
        Point& translate(double tx, double ty) {
            return set(x - tx, y - ty);
        }
        Point& rotate(double theta) {
            double cosTheta = cos(theta);
            double sinTheta = sin(theta);
            return set(
                x * cosTheta - y * sinTheta,
                x * sinTheta + y * cosTheta
            );
        }
};

#endif
