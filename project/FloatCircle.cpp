#include "FloatCircle.hpp"

FloatCircle::FloatCircle(float x, float y, float radius)
: x(x)
, y(y)
, radius(radius)
{

}

bool FloatCircle::intersects(const FloatCircle& circle)
{
    if(radius + circle.radius > sqrt(pow((circle.x - x), 2) + pow((circle.y - y), 2)))
        return true;
    else
        return false;
}

int FloatCircle::getAngle(const FloatCircle& circle)
{
    double angle = atan2(circle.x - x, circle.y - y) * (180 / M_PI);

    if(angle < 0)
        angle += 360;

    angle = 360 - angle;

    int result = static_cast<int>(angle);

    if(angle - result >= 0.5)
        result += 1;

    result %= 360;
    return result;
}

