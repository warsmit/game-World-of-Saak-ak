#include "TextureManager.hpp"

TextureManager::TextureManager()
:mTextureList()
{

}

void TextureManager::loadTexture(TextureID id, const std::string name)
{
    auto texture = new sf::Texture();
    if(!texture->loadFromFile(name))
        std::cout << "Error load from file: " << name << std::endl;
    else
        mTextureList.insert(std::pair<TextureID, sf::Texture*>(id, texture));
}

sf::Texture& TextureManager::getTexture(TextureID id)
{
    auto found = mTextureList.find(id);
    assert(found != mTextureList.end());
    return *found->second;
}
