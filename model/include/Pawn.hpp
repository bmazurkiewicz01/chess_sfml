#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece
{
public:
    Pawn(sf::Texture& texture) : Piece(texture) {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        target.draw(m_pieceSprite, states);
    }
};

#endif
