#include <SFML/Graphics.hpp>
#include <array>
#include "Tile.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess SFML");
    std::array<std::array<Tile, 8>, 8> board;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            sf::Color tileColor = (x + y) % 2 == 0 ? sf::Color::White : sf::Color::Black;
            board[y][x] = Tile(100.f, x, y, tileColor);
            // std::cout << board[y][x] << std::endl;
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    for (const auto& row : board) 
                    {
                        for (const auto& tile : row) 
                        {
                            if (tile.containsPoint(mousePosition))
                            {
                                std::cout << "Clicked on tile:" << std::endl << tile << std::endl;
                            }
                        }
                    }
                }
            }
        }

        window.clear();
        for (const auto& row : board) 
        {
            for (const auto& tile : row) 
            {
                window.draw(tile);
            }
        }
        window.display();
    }

    return 0;
}