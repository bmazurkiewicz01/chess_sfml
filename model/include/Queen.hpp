#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"

class Queen : public Piece
{
public:
    Queen(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor);
    void calculateValidMoves(BoardType board, bool simulateMoves = false) const override;
};

#endif
