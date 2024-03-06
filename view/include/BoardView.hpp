#ifndef BOARD_VIEW_HPP
#define BOARD_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "Tile.hpp"
#include "BoardUtils.hpp"
#include "TextureManager.hpp"
#include "PromotionModalView.hpp"

class BoardView 
{
private:
    sf::RenderWindow& m_window;
    BoardType m_board;
    TextureManager m_textureManager;
    std::unique_ptr<PromotionModalView> m_promotionModalView;
    
    void initializePawn(PieceColor color, int x, int y, int direction);
    void initializeBackRow(PieceColor color, int y);
    PieceColor getOppositeColor(PieceColor color) const;

public:
    BoardView(sf::RenderWindow& window, TextureManager textureManager);

    void initializeBoard(PieceColor playerColor);
    void handleEvents();
    void drawBoard() const;
    void drawMoveHint(std::vector<Tile> validMoves) const;
    void createPromotionDialog(PieceColor playerColor, const sf::Vector2f& position);
    void drawPromotionDialog();
    sf::RenderWindow& getWindow();
    BoardType& getBoard();
    TextureManager& getTextureManager();
};

#endif
