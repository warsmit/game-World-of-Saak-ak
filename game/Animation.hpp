#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Animation
{
public:
    Animation();
    void update(float time);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    void setRotation(float angle);
    void setting(sf::Texture& texture, int x, int y, int width, int height, int countFrames, float speedAnimation, int stepFrames, bool flipAnimation, bool loopAnimation);
    void flip(bool flip);
    void pause();
    void play();
    bool isPlaying();
    void setLoop(bool loop);
    void reset();
private:
    std::vector<sf::IntRect> mFrames;
    std::vector<sf::IntRect> mFramesFlip;
    float mCurrentFrame;
    float mSpeed;
    bool mLoop;
    bool mFlip;
    bool mIsPlaying;
    sf::Sprite mSprite;

};

#endif // ANIMATION_H
