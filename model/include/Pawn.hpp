#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece
{
private:
    mutable bool m_firstMove;
    mutable bool m_exposedOnEnPassant;
    mutable int m_direction;

    bool isMovingForward(int y) const;
    bool isPathClear(int y, BoardType board) const;
public:
    Pawn(sf::Texture& texture, int x, int y, PieceColor pieceColor, int direction);

    bool isValidMove(const Tile& tile, BoardType board, bool simulateMove = false) const override;
    void calculateValidMoves(BoardType board, bool simulateMoves = false) const override;

    bool canPromote(int y) const;

    bool getExposedOnEnPassant() const;
    void setExposedOnEnPassant(bool exposed) const;

    int getDirection() const;
};

#endif
