#ifndef BOARD_VIEW_HPP
#define BOARD_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "Tile.hpp"
#include "BoardUtils.hpp"
#include "TextureManager.hpp"

class BoardView 
{
private:
    sf::RenderWindow& m_window;
    BoardType m_board;
    TextureManager m_textureManager;
    

public:
    BoardView(sf::RenderWindow& window, TextureManager textureManager);

    void initializeBoard();
    void handleEvents();
    void drawBoard() const;
    void drawMoveHint(std::vector<Tile> validMoves) const;
    sf::RenderWindow& getWindow();
    BoardType& getBoard();
};

#endif
