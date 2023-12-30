#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece
{
private:
    mutable bool m_firstMove;

    bool isMovingForward(int y) const;
    bool canPromote(int y) const;
    bool isPathClear(int y, std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> board) const;
    bool resultsInCheck(int targetY, int targetX, const std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE>& board) const;
public:
    Pawn(sf::Texture& texture, int x, int y, PieceColor pieceColor);

    bool isValidMove(const Tile& tile, std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> board) const override;
    void calculateValidMoves(std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> board, bool simulateMoves = false) const override;
};

#endif
