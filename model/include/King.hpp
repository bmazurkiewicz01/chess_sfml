#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece
{
private:
    mutable bool m_firstMove;
public:
    King() = default;
    King(sf::Texture& texture, int x, int y, PieceColor pieceColor);

    bool isValidMove(const Tile& tile, std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> board, bool simulateMove = false) const override;
    void calculateValidMoves(std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> board, bool simulateMoves = false) const override;
};

#endif