#include "Meteor.hpp"

Meteor::Meteor(float x, float y, float speed, int flightAngle, int width, int height)
: Entity(x, y, speed, flightAngle, width, height)
, mDeceleration(2000)
{

}

Meteor::~Meteor()
{

}

void Meteor::settledPosition(float time)
{
    if(mSpeed > 0)
    {
        mSpeed -= mDeceleration * time;
        if(mSpeed < 0)
            mSpeed = 0;
    }

    mDX = mSpeed * (sin(mFlightAngle / (180 / M_PI)));
    mDY = mSpeed * (cos(mFlightAngle / (180 / M_PI))) * -1;

    mBody.x += mDX * time;
    mBody.y += mDY * time;
    mDX = 0;
    mDY = 0;
}

void Meteor::collosion()
{
    if((mBody.x < 0 + mWidth / 2) || (mBody.x > WIDTH -  mWidth / 2))
    {
        if(mBody.x < 0 + mWidth / 2)
            mBody.x = mHeight / 2;
        else
            mBody.x = WIDTH - mWidth / 2;

        if(mFlightAngle == 0 || mFlightAngle == 180)
            mFlightAngle += 180;
        else
            mFlightAngle = 360 - mFlightAngle;

        mFlightAngle %= 360;
    }

    if((mBody.y < 0 + mHeight / 2) || (mBody.y > HEIGHT - mHeight / 2))
    {
        if(mBody.y < 0 + mHeight / 2)
            mBody.y = mHeight / 2;
        else
            mBody.y = HEIGHT - mHeight / 2;

        if(mFlightAngle == 0 || mFlightAngle == 180)
            mFlightAngle += 180;
        else
            mFlightAngle = 360 - mFlightAngle + 180;

        mFlightAngle %= 360;
    }
}

void Meteor::update(float deltaTime)
{
    mAnimationManager.update(deltaTime);
    collosion();
    settledPosition(deltaTime);
}

void Meteor::draw(sf::RenderWindow& window)
{
    Entity::draw(window);
}

void Meteor::createAnimations(TextureManager& textureManager)
{
    sf::Texture& texture = textureManager.getTexture(TextureID::PlayerTexture);
    mAnimationManager.createAnimation(MeteorAnimationStay, texture, 65, 344, 64, 64, 1, 0, 64, false, true);
    mAnimationManager.setAnimation(MeteorAnimationStay);
}
