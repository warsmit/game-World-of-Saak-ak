#ifndef METEOR_H
#define METEOR_H

#include "Entity.hpp"

class Meteor : public Entity
{
public:
    Meteor(float x, float y, float speed, int flightAngle, int width, int height);
    virtual ~Meteor();
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window);
    virtual void createAnimations(TextureManager& textureManager);
    void settledPosition(float time);
    void collosion();
private:
    int mDeceleration;
};

#endif // METEOR_H
