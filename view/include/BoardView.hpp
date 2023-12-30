#ifndef BOARD_VIEW_HPP
#define BOARD_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "Tile.hpp"
#include "BoardUtils.hpp"

class BoardView 
{
private:
    sf::Texture whitePawnTexture;
    sf::Texture blackPawntexture;
    sf::RenderWindow& m_window;

    std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE> m_board;

public:
    BoardView(sf::RenderWindow& window);

    void initializeBoard();
    void handleEvents();
    void drawBoard() const;
    void drawMoveHint(std::vector<Tile> validMoves) const;
    sf::RenderWindow& getWindow();
    const std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE>& getBoard() const;
};

#endif
