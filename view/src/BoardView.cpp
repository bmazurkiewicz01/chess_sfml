#include "BoardView.hpp"
#include "EventManager.hpp"
#include "Pawn.hpp"

BoardView::BoardView(sf::RenderWindow& window) : m_window(window)
{
    
}

void BoardView::initializeBoard()
{
    whitePawnTexture.loadFromFile("../resources/white-pawn.png");
    blackPawntexture.loadFromFile("../resources/black-pawn.png");
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            sf::Color tileColor = (x + y) % 2 == 0 ? sf::Color::White : sf::Color::Green;
            m_board[y][x] = Tile(100.f, x, y, tileColor);

            if(y == 1)
            {
                PieceColor pieceColor = tileColor == sf::Color::White ? PieceColor::WHITE : PieceColor::BLACK;
                Pawn pawn(blackPawntexture, x, y, pieceColor);
                m_board[y][x].setPiece(std::make_shared<Pawn>(pawn));
            }
            else if(y == 6)
            {
                PieceColor pieceColor = tileColor == sf::Color::White ? PieceColor::WHITE : PieceColor::BLACK;
                Pawn pawn(whitePawnTexture, x, y, pieceColor);
                m_board[y][x].setPiece(std::make_shared<Pawn>(pawn));
            }
        }
    }
}

void BoardView::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f mousePosition = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                for (auto& row : m_board) 
                {
                    for (auto& tile : row) 
                    {
                        if (tile.containsPoint(mousePosition))
                        {
                            std::cout << "Original address: " << &tile << std::endl; 
                            EventManager::getInstance().publish<Tile>(EventType::ON_TILE_PRESSED, std::shared_ptr<Tile>{&tile, [](Tile*){}});
                        }
                    }
                }
            }
        }
        //     else if (event.mouseButton.button == sf::Mouse::Right)
        //     {
        //         for (auto& row : m_board) 
        //         {
        //             for (auto& tile : row) 
        //             {
        //                 if (tile.containsPoint(mousePosition))
        //                 {
        //                     tile.setPiece(nullptr);
        //                     std::cout << "Clicked on tile:" << std::endl << tile << std::endl;
        //                 }
        //             }
        //         }
        //     }
        // }
    }
}

void BoardView::drawBoard() const
{
    m_window.clear();
    for (const auto& row : m_board) 
    {
        for (const auto& tile : row) 
        {
            m_window.draw(tile);
        }
    }
    m_window.display();
}

sf::RenderWindow& BoardView::getWindow()
{
    return m_window;
}

