#ifndef BULLET_H
#define BULLET_H

#include "Entity.hpp"

class Bullet : public Entity
{
public:
    Bullet(float x, float y, float speed, int width, int height, int flightAngle, int numPlayer);
    virtual ~Bullet();
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window);
    virtual void createAnimations(TextureManager& textureManager);
    void reduceStability();
    void updateAnimation(float time);
    bool isPlaying();
    void settledPosition(float time);
    void collosion();
    int getNumPlayer();
private:
    int mStability;
    int mNumPlayer;
};

#endif // BULLET_H
