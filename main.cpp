#include "BoardView.hpp"
#include "BoardController.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess SFML");
    
    BoardView boardView(window);
    boardView.initializeBoard();

    BoardController boardController(boardView);
    boardController.run();
    
    return 0;
}