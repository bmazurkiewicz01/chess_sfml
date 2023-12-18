#ifndef BOARD_VIEW_HPP
#define BOARD_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "Tile.hpp"

class BoardView 
{
private:
    sf::Texture whitePawnTexture;
    sf::RenderWindow& m_window;
    std::array<std::array<Tile, 8>, 8> m_board;

public:
    BoardView(sf::RenderWindow& window);

    void initializeBoard();
    void handleEvents();
    void drawBoard() const;
    sf::RenderWindow& getWindow();
};

#endif
