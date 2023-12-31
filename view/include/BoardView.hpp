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
    // temporary storage for textures
    // TODO: create better solution
    sf::Texture whitePawnTexture;
    sf::Texture blackPawnTexture;
    sf::Texture whiteKingTexture;
    sf::Texture blackKingTexture;
    sf::RenderWindow& m_window;

    BoardType m_board;

public:
    BoardView(sf::RenderWindow& window);

    void initializeBoard();
    void handleEvents();
    void drawBoard() const;
    void drawMoveHint(std::vector<Tile> validMoves) const;
    sf::RenderWindow& getWindow();
    const BoardType& getBoard() const;
};

#endif
