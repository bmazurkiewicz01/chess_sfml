#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"

class Rook : public Piece
{
private:
    mutable bool m_firstMove;

public:
    Rook(sf::Texture& pieceTexture, int x, int y, PieceColor pieceColor);

    bool isValidMove(const Tile& tile, BoardType board, bool simulateMove = false) const override;
    void calculateValidMoves(BoardType board, bool simulateMoves = false) const override;

    bool isFirstMove();
};

#endif
