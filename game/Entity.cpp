#include "Entity.hpp"

Entity::Entity(float x, float y, float speed, int flightAngle, int width, int height)
:mSpeed(speed)
,mWidth(width)
,mHeight(height)
,mAnimationManager()
,mDX(0.f)
,mDY(0.f)
,mIsAlive(true)
,mBody(x, y, mWidth /2 )
,mFlightAngle(flightAngle)
{

}

Entity::~Entity()
{

}

void Entity::draw(sf::RenderWindow& window)
{
    mAnimationManager.setPosition(mBody.x, mBody.y);
    mAnimationManager.draw(window);
}

FloatCircle& Entity::getBody()
{
    return mBody;
}

bool Entity::isAlive()
{
    return mIsAlive;
}

void Entity::die()
{
    mIsAlive = false;
}

void Entity::setSpeed(float speed)
{
    mSpeed = speed;
}

float Entity::getSpeed()
{
    return mSpeed;
}

void Entity::setFlightAngle(float angle)
{
    mFlightAngle = angle;
}

void Entity::reborn()
{
    mIsAlive = true;
}

int Entity::getFlightAngle()
{
    return mFlightAngle;
}

sf::Vector2f Entity::getDSpeed()
{
    return sf::Vector2f(mDX, mDY);
}

void Entity::setDSpeed(float dX, float dY)
{
    mDX = dX;
    mDY = dY;

    double angle = atan2(mDX, mDY) * (180 / M_PI);

    if(angle < 0)  angle += 360;

    angle = 360 - angle;

    int result = static_cast<int>(angle);

    if(angle - result >= 0.5)  result += 1;

    result %= 360;
}
