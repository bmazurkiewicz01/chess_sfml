#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece
{
private:
    mutable bool m_firstMove;

    bool isMovingForward(int y) const;
    bool canPromote(int y) const;
    bool isPathClear(int y, std::array<std::array<Tile, 8>, 8> board) const;
public:
    Pawn(sf::Texture& texture, int x, int y, PieceColor pieceColor);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool move(Tile& tile, Tile& clickedTile, std::array<std::array<Tile, 8>, 8> board) override;
    bool isValidMove(const Tile& tile, std::array<std::array<Tile, 8>, 8> board) const override;
};

#endif
