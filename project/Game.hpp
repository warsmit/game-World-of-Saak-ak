#ifndef GAME_H
#define GAME_H

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include "World.hpp"
#include "TextureManager.hpp"

#include "Helper.hpp"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

private:
    sf::RenderWindow mWindow;
    TextureManager mTextureManager;
    World mWorld;
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
};

#endif // GAME_H
