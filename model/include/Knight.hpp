#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

class Knight : public Piece
{
public:
    Knight(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor);
    void calculateValidMoves(BoardType board, bool simulateMoves = false) const override;
};

#endif
