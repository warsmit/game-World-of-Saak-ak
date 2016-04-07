#include "Game.hpp"

Game::Game()
: mWindow(sf::VideoMode(WIDTH, HEIGHT), "SFML Application")
, mWorld()
{
    mWindow.setFramerateLimit(60);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::update(sf::Time deltaTime)
{
    float time = deltaTime.asSeconds();
    mWorld.update(time);
}

void Game::render()
{
    mWindow.clear();
    mWorld.draw(mWindow);
    mWindow.display();
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();
        else
            mWorld.handleEvents(event);
    }
}
