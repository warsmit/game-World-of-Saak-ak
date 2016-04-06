#include "Animation.hpp"

Animation::Animation()
: mFrames()
, mFramesFlip()
, mCurrentFrame(0.f)
, mSpeed(0.f)
, mLoop(false)
, mFlip(false)
, mIsPlaying(true)
, mSprite()
{

}

void Animation::update(float time)
{
    if(!mIsPlaying)
        return;

    mCurrentFrame += mSpeed * time;

    if(mCurrentFrame > mFrames.size())
    {
        mCurrentFrame -= mFrames.size();
        if(!mLoop)
        {
            mIsPlaying = false;
            return;
        }
    }

    if(mFlip)
        mSprite.setTextureRect(mFramesFlip[static_cast<int>(mCurrentFrame)]);
    else
        mSprite.setTextureRect(mFrames[static_cast<int>(mCurrentFrame)]);
}

void Animation::setting(sf::Texture& texture, int x, int y, int width, int height, int countFrames, float speedAnimation, int stepFrames, bool flipAnimation, bool loopAnimation)
{
    mSpeed = speedAnimation;
    mLoop = loopAnimation;
    mFlip = flipAnimation;
    mSprite.setTexture(texture);
    mSprite.setOrigin(width / 2, height / 2);
    for(int i = 0; i < countFrames; ++i)
    {
        mFrames.push_back(sf::IntRect(x + i * stepFrames, y, width, height));
        mFramesFlip.push_back(sf::IntRect(x + i * stepFrames + width, y, -width, height));
    }

    if(mFlip)
        mSprite.setTextureRect(mFramesFlip[0]);
    else
        mSprite.setTextureRect(mFrames[0]);
}

void Animation::draw(sf::RenderWindow& window)
{
    window.draw(mSprite);
}

void Animation::setPosition(float x, float y)
{
    mSprite.setPosition(x, y);
}

void Animation::setRotation(float angle)
{
    mSprite.setRotation(angle);
}

void Animation::flip(bool flip)
{
    mFlip = flip;
}

void Animation::pause()
{
    mIsPlaying = false;
}

void Animation::play()
{
    mIsPlaying = true;
}

bool Animation::isPlaying()
{
    return mIsPlaying;
}

void Animation::setLoop(bool loop)
{
    mLoop = loop;
}

void Animation::reset()
{
     mCurrentFrame = 0;
     play();
}
