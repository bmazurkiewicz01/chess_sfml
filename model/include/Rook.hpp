#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"

class Rook : public Piece
{
public:
    Rook(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor);
    void calculateValidMoves(BoardType board, bool simulateMoves = false) const override;
};

#endif
