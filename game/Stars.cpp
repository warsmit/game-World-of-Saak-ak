#include "Stars.hpp"

Stars::Stars(float x, float y, float speed, int width, int height, int flightAngle, int type, int timeLife)
: Entity(x, y, speed, flightAngle, width, height)
, mType(type)
, mTimeLife(timeLife / 100.f)
{

}

Stars::~Stars()
{

}

void Stars::update(float deltaTime)
{
    mAnimationManager.update(deltaTime);
    mTimeLife -= deltaTime;


    if(mTimeLife < 0)
    {
        mIsAlive = false;
        mAnimationManager.setLoop(false);
    }
}

void Stars::draw(sf::RenderWindow& window)
{
    Entity::draw(window);
}

void Stars::createAnimations(TextureManager& textureManager)
{
    sf::Texture& texture = textureManager.getTexture(TextureID::StarsTexture);

    mAnimationManager.createAnimation(starsAnimation, texture, 0,mType * 5, 5, 5, 9, 5, 5, false, true);
    mAnimationManager.setAnimation(AnimationID::starsAnimation);
}

bool Stars::isPlaying()
{
    return mAnimationManager.isPlaying();
}


