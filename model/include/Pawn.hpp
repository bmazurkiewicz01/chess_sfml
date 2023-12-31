#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece
{
private:
    mutable bool m_firstMove;

    bool isMovingForward(int y) const;
    bool canPromote(int y) const;
    bool isPathClear(int y, BoardType board) const;
public:
    Pawn(sf::Texture& texture, int x, int y, PieceColor pieceColor);

    bool isValidMove(const Tile& tile, BoardType board, bool simulateMove = false) const override;
    void calculateValidMoves(BoardType board, bool simulateMoves = false) const override;
};

#endif
