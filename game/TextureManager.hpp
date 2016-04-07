#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <map>
#include <string>
#include <iostream>
#include <cassert>
#include <SFML/Graphics/Texture.hpp>

enum TextureID
{
    PlayerTexture,
    BackGround,
    StarsTexture
};

class TextureManager
{
public:
    TextureManager();
    void loadTexture(TextureID id, const std::string name);
    sf::Texture& getTexture(TextureID id);
private:
    std::map<TextureID, sf::Texture*> mTextureList;
};

#endif // TEXTUREMANAGER_H
