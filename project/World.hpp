#ifndef WORLD_H
#define WORLD_H

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <random>
#include <time.h>

#include "Player.hpp"
#include "TextureManager.hpp"
#include "Bullet.hpp"
#include "Meteor.hpp"
#include "Stars.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>


#include <algorithm>

#include <sstream>

class Context
{
public:
    Context(TextureManager& textureManager, std::vector<Bullet*>& bulletList, std::vector<Meteor*>& meteorList);
    TextureManager* mTextureManager;
    std::vector<Bullet*>* mBulletList;
    std::vector<Meteor*>* mMeteorList;
};

class World
{
public:
    World();
    void handleEvents(const sf::Event event);
    void update(float time);
    void draw(sf::RenderWindow& window);
private:
    TextureManager mTextureManager;
    std::vector<Bullet*> mBulletList;
    std::vector<Meteor*> mMeteorList;
    Context mContext;
    std::vector<Player*> mPlayerList;
    std::vector<Stars*> mStarsList;
    sf::Font mFont;
    sf::Text mText;
    bool hasWin;
    const int mMaxKILL = 5;
    const size_t mMaxPlayers = 4;
    sf::Music mMainTime;
    sf::Music mWinTime;

};

#endif // WORLD_H
