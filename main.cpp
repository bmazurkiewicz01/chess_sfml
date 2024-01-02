#include "BoardView.hpp"
#include "BoardController.hpp"
#include "TextureManager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess SFML");
    TextureManager textureManager;
    
    BoardView boardView(window, textureManager);
    boardView.initializeBoard();

    BoardController boardController(boardView);
    boardController.run();
    
    return 0;
}