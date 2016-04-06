#ifndef STARS_H
#define STARS_H

#include "Entity.hpp"

class Stars : public Entity
{
public:
    Stars();
    Stars(float x, float y, float speed, int width, int height, int flightAngle, int type, int timeLife);
    virtual ~Stars();
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window);
    virtual void createAnimations(TextureManager& textureManager);
    bool isPlaying();
private:
    int mType;
    float mTimeLife;
};



#endif // STARS_H
