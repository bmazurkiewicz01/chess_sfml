#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece
{
private:
    mutable bool m_firstMove;
    
    bool canCastleKingside(BoardType board) const;
    bool canCastleQueenside(BoardType board) const;
public:
    King() = default;
    King(sf::Texture& texture, int x, int y, PieceColor pieceColor);

    bool isValidMove(const Tile& tile, BoardType board, bool simulateMove = false) const override;
    void calculateValidMoves(BoardType board, bool simulateMoves = false) const override;
};

#endif