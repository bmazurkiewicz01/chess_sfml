#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"

class Bishop : public Piece
{
public:
    Bishop(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor);
    void calculateValidMoves(BoardType board, bool simulateMoves = false) const override;
};

#endif
