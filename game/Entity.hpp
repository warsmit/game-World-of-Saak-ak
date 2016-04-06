#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Joystick.hpp>
#include <map>
#include <math.h>

#include "TextureManager.hpp"
#include "AnimationManager.hpp"
#include "FloatCircle.hpp"

#include "SFML/Audio.hpp"


#include "Helper.hpp"

class Entity
{
public:
    Entity(float x, float y, float speed, int flightAngle, int width, int height);
    virtual ~Entity();
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window);
    FloatCircle& getBody();
    bool isAlive();
    virtual void die();
    virtual void reborn();
    void setSpeed(float speed);
    float getSpeed();
    void setFlightAngle(float angle);
    int getFlightAngle();
    virtual void createAnimations(TextureManager& textureManager) = 0;

    sf::Vector2f getDSpeed();
    void setDSpeed(float dX, float dY);
protected:
    float mSpeed;
    const int mWidth;
    const int mHeight;
    AnimationManager mAnimationManager;
    float mDX;
    float mDY;
    bool mIsAlive;
    FloatCircle mBody;
    int mFlightAngle;
};

#endif // ENTITY_H
