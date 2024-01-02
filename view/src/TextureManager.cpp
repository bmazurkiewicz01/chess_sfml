#include "TextureManager.hpp"

TextureManager::TextureManager()
{

}

void TextureManager::loadPieceTexture(PieceType type, PieceColor color, const std::string& filePath)
{
    sf::Texture texture;
    if (texture.loadFromFile(filePath))
    {
        pieceTextures[std::make_pair(type, color)] = texture;
    }
    else
    {
        throw std::runtime_error("Failed to load texture from file: " + filePath);
    }
}

sf::Texture& TextureManager::getPieceTexture(PieceType type, PieceColor color)
{
    auto it = pieceTextures.find(std::make_pair(type, color));
    if (it != pieceTextures.end())
    {
        return it->second;
    }
    else
    {
        throw std::out_of_range("Texture not found for piece type and color");
    }
}
