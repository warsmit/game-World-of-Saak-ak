#include "AnimationManager.hpp"

AnimationManager::AnimationManager()
: mCurrentAnimationID(AnimationNope)
, mAnimationList()
{

}

void AnimationManager::createAnimation(AnimationID id, sf::Texture& texture, int x, int y, int width, int height, int countFrames, float speedAnimation, int stepFrames, bool flipAnimation, bool loopAnimation)
{
    Animation animation;
    animation.setting(texture, x, y, width, height, countFrames, speedAnimation, stepFrames, flipAnimation, loopAnimation);
    mAnimationList[id] = animation;
    mCurrentAnimationID = id;
}

void AnimationManager::setPosition(float x, float y)
{
    mAnimationList[mCurrentAnimationID].setPosition(x, y);
}

void AnimationManager::setRotation(float angle)
{
    mAnimationList[mCurrentAnimationID].setRotation(angle);
}


void AnimationManager::draw(sf::RenderWindow& window)
{
//    mAnimationList[mCurrentAnimationID].setPosition(x, y);
    mAnimationList[mCurrentAnimationID].draw(window);
}

void AnimationManager::setAnimation(AnimationID id)
{
    mCurrentAnimationID = id;
}

void AnimationManager::flip(bool flip)
{
    mAnimationList[mCurrentAnimationID].flip(flip);
}

void AnimationManager::update(float time)
{
    mAnimationList[mCurrentAnimationID].update(time);
}

void AnimationManager::pause()
{
    mAnimationList[mCurrentAnimationID].pause();
}

void AnimationManager::play()
{
    mAnimationList[mCurrentAnimationID].play();
}

bool AnimationManager::isPlaying()
{
    return mAnimationList[mCurrentAnimationID].isPlaying();
}

void AnimationManager::setLoop(bool loop)
{
    mAnimationList[mCurrentAnimationID].setLoop(loop);
}

void AnimationManager::reset()
{
    mAnimationList[mCurrentAnimationID].reset();
}
