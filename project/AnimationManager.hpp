#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <map>

#include "Animation.hpp"

enum AnimationID
{
    AnimationNope,
    PlayerAnimationStay,
    PlayerAnimationMove,
    PlayerAnimationDie,

    BulletAnimationMove,
    BulletAnimationDie,

    MeteorAnimationStay,
    starsAnimation
};

class AnimationManager
{
public:
    AnimationManager();
    void createAnimation(AnimationID id, sf::Texture& texture, int x, int y, int width, int height, int countFrames, float speedAnimation, int stepFrames, bool flipAnimation, bool loopAnimation);
    void draw(sf::RenderWindow& window);
    void setAnimation(AnimationID id);
    void setPosition(float x, float y);
    void setRotation(float angle);
    void flip(bool flip);
    void update(float time);
    void pause();
    void play();
    bool isPlaying();
    void setLoop(bool loop);
    void reset();
private:
    AnimationID mCurrentAnimationID;
    std::map<AnimationID, Animation> mAnimationList;

};

#endif // ANIMATIONMANAGER_H
