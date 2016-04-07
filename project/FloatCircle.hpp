#ifndef FLOATCIRCLE_H
#define FLOATCIRCLE_H

#include <math.h>

const float M_PI = 3.14159265358979323846;

struct FloatCircle
{
public:
    FloatCircle(float x, float y, float radius);
    float x;
    float y;
    float radius;
    bool intersects(const FloatCircle& circle);
    int getAngle(const FloatCircle& circle);
};

#endif // FLOATCIRCLE_H
