#ifndef EN_PASSANT_MANAGER_HPP
#define EN_PASSANT_MANAGER_HPP

#include <queue>
#include "Pawn.hpp"

class EnPassantManager
{
private:
    std::queue<const Pawn*> m_pawns;

    EnPassantManager() = default;
    EnPassantManager(const EnPassantManager&) = delete;
    EnPassantManager& operator=(const EnPassantManager&) = delete;

public:
    static EnPassantManager& getInstance();

    void registerPawn(const Pawn* pawn);
    void popPawn();
};

#endif
