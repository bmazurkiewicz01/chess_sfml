#ifndef KING_CHECKER_HPP
#define KING_CHECKER_HPP

#include <memory>
#include "King.hpp"
#include "Tile.hpp"

class KingChecker 
{
private:
    friend class King;
    std::shared_ptr<King> m_whiteKing;
    std::shared_ptr<King> m_blackKing;

    KingChecker();
    KingChecker(const KingChecker&) = delete;
    KingChecker& operator=(const KingChecker&) = delete;

    bool isKingInCheck(const King& king, const std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE>& board) const;
public:
    static KingChecker& getInstance();

    void setWhiteKing(std::shared_ptr<King> king);
    void setBlackKing(std::shared_ptr<King> king);

    bool isWhiteKingInCheck(const std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE>& board) const;
    bool isBlackKingInCheck(const std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE>& board) const;
};

#endif
