#include "EnPassantManager.hpp"

EnPassantManager& EnPassantManager::getInstance()
{
    static EnPassantManager instance;
    return instance;
}

void EnPassantManager::registerPawn(const Pawn* pawn)
{
    if (pawn) 
    {
        pawn->setExposedOnEnPassant(true);
        m_pawns.push(pawn);
    }
}

void EnPassantManager::popPawn()
{
    if (!m_pawns.empty()) 
    {
        const Pawn* pawn = m_pawns.front();
        if (pawn) 
        {
            pawn->setExposedOnEnPassant(false);
        }
        m_pawns.pop();
    }
}