#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "Piece.hpp" 

class TextureManager
{
private:
    std::map<std::pair<PieceType, PieceColor>, sf::Texture> pieceTextures;

public:
    TextureManager();
    void loadPieceTexture(PieceType type, PieceColor color, const std::string& filePath);
    sf::Texture& getPieceTexture(PieceType type, PieceColor color);
};

#endif