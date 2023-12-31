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

    bool isKingInCheck(const King& king, const BoardType& board) const;
public:
    static KingChecker& getInstance();

    void setWhiteKing(std::shared_ptr<King> king);
    void setBlackKing(std::shared_ptr<King> king);

    bool isWhiteKingInCheck(const BoardType& board) const;
    bool isBlackKingInCheck(const BoardType& board) const;
    bool isCheckmate(const BoardType& board, PieceColor pieceColor) const;
};

#endif
