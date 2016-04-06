#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float speed, int width, int height, int flightAngle, int numPlayer)
: Entity(x, y, speed, flightAngle, width, height)
, mStability(3)
, mNumPlayer(numPlayer)
{

}

Bullet::~Bullet()
{

}

void Bullet::updateAnimation(float time)
{
    if(mIsAlive)        mAnimationManager.setAnimation(AnimationID::BulletAnimationMove);
    else                mAnimationManager.setAnimation(AnimationID::BulletAnimationDie);

    mAnimationManager.update(time);
}

void Bullet::settledPosition(float time)
{
    if(mDX==0) mDX = mSpeed * (sin(mFlightAngle / (180 / M_PI)));
    if(mDY==0) mDY = mSpeed * (cos(mFlightAngle / (180 / M_PI))) * -1;

    mBody.x += mDX * time;
    mBody.y += mDY * time;
}

void Bullet::collosion()
{

    if(mBody.x < 0 + mWidth / 2)
    {
        mDX *= -1;
        reduceStability();
        mBody.x = 0 + mWidth / 2;
    }

    if(mBody.x > WIDTH -  mWidth / 2)
    {
        mDX *= -1;
        reduceStability();
        mBody.x = WIDTH -  mWidth / 2;
    }


    if(mBody.y < 0 + mHeight / 2)
    {
        mDY *=-1;
        reduceStability();
        mBody.y = 0 + mHeight / 2;
    }

    if(mBody.y > HEIGHT - mHeight / 2)
    {
        mDY *=-1;
        reduceStability();
        mBody.y = HEIGHT - mHeight / 2;
    }


}

void Bullet::update(float deltaTime)
{
    updateAnimation(deltaTime);

    if(!mIsAlive) return;

    collosion();
    settledPosition(deltaTime);
}

void Bullet::draw(sf::RenderWindow& window)
{
    Entity::draw(window);
}

void Bullet::createAnimations(TextureManager& textureManager)
{
    sf::Texture& texture = textureManager.getTexture(TextureID::PlayerTexture);
    mAnimationManager.createAnimation(BulletAnimationMove, texture, 18, 258 + mNumPlayer * 22, 18, 18, 2, 10, 18, false, true);
    mAnimationManager.createAnimation(BulletAnimationDie, texture, 54, 256 + mNumPlayer * 22, 22, 22, 2, 10, 22, false, false);
    mAnimationManager.setAnimation(BulletAnimationMove);
}

void Bullet::reduceStability()
{
    if(mIsAlive)
    {
        --mStability;
        if(mStability <= 0)
            mIsAlive = false;
    }
}

bool Bullet::isPlaying()
{
    return mAnimationManager.isPlaying();
}

int Bullet::getNumPlayer()
{
    return mNumPlayer;
}


