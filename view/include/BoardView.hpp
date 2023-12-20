#ifndef BOARD_VIEW_HPP
#define BOARD_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "Tile.hpp"

class BoardView 
{
private:
    sf::Texture whitePawnTexture;
    sf::Texture blackPawntexture;
    sf::RenderWindow& m_window;

    std::array<std::array<Tile, 8>, 8> m_board;

public:
    BoardView(sf::RenderWindow& window);

    void initializeBoard();
    void handleEvents();
    void drawBoard() const;
    sf::RenderWindow& getWindow();
    const std::array<std::array<Tile, 8>, 8>& getBoard() const;
};

#endif
