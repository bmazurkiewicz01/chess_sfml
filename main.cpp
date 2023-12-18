#include "BoardView.hpp"
#include "BoardController.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess SFML");
    BoardView boardView(window);
    boardView.initializeBoard();
    BoardController boardController(boardView);

    boardController.run();
    // sf::RenderWindow window(sf::VideoMode(800, 800), "Chess SFML");
    // std::array<std::array<Tile, 8>, 8> board;
    // for (int y = 0; y < 8; y++)
    // {
    //     for (int x = 0; x < 8; x++)
    //     {
    //         sf::Color tileColor = (x + y) % 2 == 0 ? sf::Color::White : sf::Color::Green;
    //         board[y][x] = Tile(100.f, x, y, tileColor);
    //     }
    // }

    // sf::Texture blackPawnTexture;
    // blackPawnTexture.loadFromFile("../resources/black-pawn.png");
    // sf::Texture whitePawnTexture;
    // whitePawnTexture.loadFromFile("../resources/white-pawn.png");

    // Pawn pawn(blackPawnTexture);
    // // pawn.setSize(sf::Vector2f(100.f, 100.f));
    // // pawn.setPosition(sf::Vector2f(board[6][1].getPosition().x, board[6][1].getPosition().y));
    // board[6][1].setPiece(std::make_shared<Pawn>(pawn));

    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //         if (event.type == sf::Event::MouseButtonPressed)
    //         {
    //             sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    //             if (event.mouseButton.button == sf::Mouse::Left)
    //             {
    //                 for (auto& row : board) 
    //                 {
    //                     for (auto& tile : row) 
    //                     {
    //                         if (tile.containsPoint(mousePosition))
    //                         {
    //                             Pawn newPawn(whitePawnTexture);
    //                             tile.setPiece(std::make_shared<Pawn>(newPawn));
    //                             std::cout << "Clicked on tile:" << std::endl << tile << std::endl;
    //                         }
    //                     }
    //                 }
    //             }
    //             else if (event.mouseButton.button == sf::Mouse::Right)
    //             {
    //                 for (auto& row : board) 
    //                 {
    //                     for (auto& tile : row) 
    //                     {
    //                         if (tile.containsPoint(mousePosition))
    //                         {
    //                             tile.setPiece(nullptr);
    //                             std::cout << "Clicked on tile:" << std::endl << tile << std::endl;
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }

    //     window.clear();
    //     for (const auto& row : board) 
    //     {
    //         for (const auto& tile : row) 
    //         {
    //             window.draw(tile);
    //             // if (tile.getPiece()) window.draw(*tile.getPiece());
    //         }
    //     }
    //     window.display();
    // }

    return 0;
}