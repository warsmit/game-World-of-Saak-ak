#include "Player.hpp"
#include "World.hpp"

Player::Player(int number, Context& context, float x, float y, float speed, int flightAngle, int width, int height)
: Entity(x, y, speed, flightAngle, width, height)
, mAction()
, mContext(context)
, mTimeToUpShot(0)
, mSprite()
, mNumber(number)
, mShield()
, mShieldTime(0.f)
{

    mShotBuf.loadFromFile("Media/Audio/sound_bullet.ogg");
    mDieBuf.loadFromFile("Media/Audio/sound_destoy.ogg");

    mShot.setBuffer(mShotBuf);
    mDie.setBuffer(mDieBuf);

    mShot.setVolume(40);
    mDie.setVolume(100);

    mSprite.setOrigin(18 / 2, 18 / 2 + 3);

    mSprite.setRotation(mFlightAngle);
    mSprite.setPosition(mBody.x, mBody.y);

    mShield.setOrigin(64 / 2, 64 / 2);

    mShield.setRotation(mFlightAngle);
    mShield.setPosition(mBody.x, mBody.y);
    mAnimationManager.setRotation(mFlightAngle);
}

Player::~Player()
{

}

void Player::tryShot(float time)
{
    if(mTimeToUpShot > 0)
        mTimeToUpShot -= time;

    if(mAction[Shot] && mTimeToUpShot <= 0)
    {
        mShot.play();
        mAction[Shot] = false;
        float bX = mBody.x + (mWidth / 2 + 5) * (sin(mFlightAngle / (180 / M_PI)));
        float bY = mBody.y + (mHeight / 2 + 5) * (cos(mFlightAngle / (180 / M_PI))) * -1;

        Bullet* bullet = new Bullet(bX, bY, 450, 10, 10, mFlightAngle, mNumber);
        bullet->createAnimations(*mContext.mTextureManager);
        mContext.mBulletList->push_back(bullet);
        mTimeToUpShot = mReloadingShot;
    }
}

void Player::updateAnimation(float time)
{
    if(mIsAlive || mShieldTime > 0)
    {
        if(mDX != 0 || mDY != 0)
            mAnimationManager.setAnimation(AnimationID::PlayerAnimationMove);
        else
            mAnimationManager.setAnimation(AnimationID::PlayerAnimationStay);
    }
    else
        mAnimationManager.setAnimation(AnimationID::PlayerAnimationDie);

    mAnimationManager.update(time);
}

void Player::update(float deltaTime)
{

    if(mIsAlive)
    {
        updateAcceleration();
        updateAnimation(deltaTime);
        settledPosition(deltaTime);
        collosion();

        if(mShieldTime <= 0)
        {
            tryShot(deltaTime);
        }else
        {
            mShieldTime -= deltaTime;
        }
    }


    if(!mIsAlive)
    {
        if(!mAnimationManager.isPlaying())
        {
            mAnimationManager.reset();
            mAnimationManager.setAnimation(AnimationID::PlayerAnimationStay);
            mAnimationManager.play();
            mShieldTime = mMaxShieldTime;
            reborn();
        }
        updateAnimation(deltaTime);
        collosion();
    }


}

void Player::settledPosition(float time)
{
    mBody.x += mDX * time;
    mBody.y += mDY * time;

    mDX = 0;
    mDY = 0;

}

void Player::updateAcceleration()
{
    if(mAction[MoveUp] || mAction[MoveDown] || mAction[MoveLeft] || mAction[MoveRight])
    {
        mDX = mSpeed * (sin(mFlightAngle / (180 / M_PI)));
        mDY = mSpeed * (cos(mFlightAngle / (180 / M_PI))) * -1;

    }
    else
    {
        mSpeed = 0;
    }
}

void Player::collosion()
{
    if(mBody.x < 0 + mWidth / 2)         mBody.x = mWidth / 2;
    else if(mBody.x > WIDTH -  mWidth / 2) mBody.x = WIDTH -  mWidth / 2;

    if(mBody.y < 0 + mHeight / 2)        mBody.y = mHeight / 2;
    else if(mBody.y > HEIGHT - mHeight / 2) mBody.y = HEIGHT - mHeight / 2;
}

void Player::draw(sf::RenderWindow& window)
{
    mAnimationManager.setRotation(mFlightAngle);

    Entity::draw(window);

    if(mIsAlive)
    {
        if(mTimeToUpShot <= 0)
        {
            mSprite.setRotation(mFlightAngle);
            mSprite.setPosition(mBody.x, mBody.y);
            window.draw(mSprite);
        }
    }

    if(mShieldTime > 0)
    {
        mShield.setRotation(mFlightAngle);
        mShield.setPosition(mBody.x, mBody.y);
        window.draw(mShield);
    }

}

void Player::createAnimations(TextureManager& textureManager)
{
    sf::Texture& texture = textureManager.getTexture(TextureID::PlayerTexture);
    mAnimationManager.createAnimation(PlayerAnimationStay, texture, 0, mNumber * 64, 64, 64, 1, 1, 64, false, true);
    mAnimationManager.createAnimation(PlayerAnimationMove, texture, 64, mNumber * 64, 64, 64, 3, 5, 64, false, true);
    mAnimationManager.createAnimation(PlayerAnimationDie, texture, 64 * 4, mNumber * 64, 64, 64, 7, 5, 64, false, false);
    mAnimationManager.setAnimation(PlayerAnimationStay);

    mSprite.setTexture(texture);
    mSprite.setTextureRect(sf::IntRect(0,258 + mNumber * 22,18,18));

    mShield.setTexture(texture);
    mShield.setTextureRect(sf::IntRect(0,344,64,64));
}

void Player::handleEvents()
{
    if(mIsAlive)
    {
        if(sf::Joystick::isConnected(mNumber))
        {
            sf::Vector2i move  = static_cast<sf::Vector2i>(sf::Vector2f(sf::Joystick::getAxisPosition(mNumber, sf::Joystick::Axis::X),
                                                                        sf::Joystick::getAxisPosition(mNumber, sf::Joystick::Axis::Y)));

            if(move.x == 0 && move.y == 0)
            {
                mDX = 0.f;
                mDY = 0.f;
                mSpeed = 0.f;
            }
            else
            {
                mDX = move.x;
                mDY = move.y;

                double angle = atan2(mDX, mDY) * (180 / M_PI);

                if(angle < 0)
                    angle += 360;

                angle = 360 - angle;

                int result = static_cast<int>(angle);

                if(angle - result >= 0.5)
                    result += 1;

                result %= 360;
                result += 180;
                result %= 360;

                mFlightAngle = result;
                mSpeed = 2.5 * (abs(move.x) > abs(move.y) ? abs(move.x) : abs(move.y));

                if(move.y > 0)  mAction[MoveUp] = true;
                else            mAction[MoveUp] = false;

                if(move.y < 0)  mAction[MoveDown] = true;
                else            mAction[MoveDown] = false;

                if(move.x > 0)  mAction[MoveRight] = true;
                else            mAction[MoveRight] = false;

                if(move.x < 0)  mAction[MoveLeft] = true;
                else            mAction[MoveLeft] = false;



            }

            if(sf::Joystick::isButtonPressed(mNumber, 0)) mAction[Shot] = true;
            else mAction[Shot] = false;
        }
    }
}

unsigned int Player::getNumber()
{
    return mNumber;
}

void Player::die()
{
    if(mShieldTime <= 0)
    {
        mSpeed = 0;
        Entity::die();
        mDie.play();
    }
}

void Player::reborn()
{
    Entity::reborn();
    //mAnimationManager.reset();
}

bool Player::hasShield()
{
    return mShieldTime <= 0 ? false : true;
}
