#ifndef PROMOTION_MODAL_DATA_HPP
#define PROMOTION_MODAL_DATA_HPP

#include <memory>
#include "Tile.hpp"
#include "Pawn.hpp"

struct PromotionModalData
{
    std::shared_ptr<Tile> clickedTile;
    std::shared_ptr<Pawn> promotionPawn;
};


#endif