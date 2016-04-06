#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <math.h>
#include "Entity.hpp"
#include "Bullet.hpp"


enum Action
{
    MoveUp,
    MoveRight,
    MoveDown,
    MoveLeft,
    Shot
};

class Context;

struct playerData
{
    float x;
    float y;
    float angle;
    bool isLocked;
    char pos;
    int result;
};

static playerData playersData[4] =
{
    {32,         32,          135, false, -1, 0},
    {WIDTH - 32, 32,          225, false, -1, 0},
    {32,         HEIGHT - 32, 45 , false, -1, 0},
    {WIDTH - 32, HEIGHT - 32, 315, false, -1, 0}
};

class Player : public Entity
{
public:
    Player(int number,Context& context, float x, float y, float speed, int flightAngle, int width, int height);
    virtual ~Player();
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window);
    virtual void die();
    void handleEvents();
    void updateAcceleration();
    virtual void createAnimations(TextureManager& textureManager);
    void tryShot(float time);
    void updateAnimation(float time);
    void settledPosition(float time);
    void collosion();
    unsigned int getNumber();
    virtual void reborn();
    bool hasShield();
protected:
    std::map<Action, bool> mAction;
    Context& mContext;
    float mTimeToUpShot;
    sf::Sprite mSprite;
    unsigned int mNumber;
    static const int mReloadingShot = 1;
    sf::Sprite mShield;
    float mShieldTime;
    const float mMaxShieldTime = 2.f;

    sf::SoundBuffer mShotBuf;
    sf::SoundBuffer mDieBuf;

    sf::Sound mShot;
    sf::Sound mDie;
};

#endif // PLAYER_H
