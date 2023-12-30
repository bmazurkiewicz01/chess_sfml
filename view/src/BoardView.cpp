#include "BoardView.hpp"
#include "EventManager.hpp"
#include "Pawn.hpp"
#include "Logger.hpp"

BoardView::BoardView(sf::RenderWindow& window) : m_window(window)
{
    
}

void BoardView::initializeBoard()
{
    m_window.setFramerateLimit(60);
    whitePawnTexture.loadFromFile("../resources/white-pawn.png");
    blackPawntexture.loadFromFile("../resources/black-pawn.png");

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            sf::Color tileColor = (x + y) % 2 == 0 ? WHITE_TILE_COLOR : BLACK_TILE_COLOR;
            m_board[y][x] = Tile(100.f, x, y, tileColor);

            if(y == 1)
            {
                Pawn pawn(blackPawntexture, x, y, PieceColor::BLACK);
                m_board[y][x].setPiece(std::make_shared<Pawn>(pawn));
            }
            else if(y == 6)
            {
                Pawn pawn(whitePawnTexture, x, y, PieceColor::WHITE);
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
                            // Logger::getInstance().log(LogLevel::DEBUG, "Tile address in BoardView: ", &tile);
                            EventManager::getInstance().publish<Tile>(EventType::ON_TILE_PRESSED, std::shared_ptr<Tile>{&tile, [](Tile*){}});
                        }
                    }
                }
            }
        }
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
}

void BoardView::drawMoveHint(std::vector<Tile> validMoves) const
{
    for (const auto& tile : validMoves)
    {
        sf::CircleShape hintCircle;
        if (tile.getPiece() == nullptr)
        {
            hintCircle.setRadius(17.5f); 
            hintCircle.setFillColor(HINT_CIRCLE_COLOR);
            hintCircle.setPosition(tile.getPosition().x + tile.getSize().x / 2 - hintCircle.getRadius(),
                                tile.getPosition().y + tile.getSize().x / 2 - hintCircle.getRadius());
        }
        else
        {
            hintCircle.setRadius(40.f);
            hintCircle.setFillColor(sf::Color::Transparent);
            hintCircle.setOutlineThickness(10.f);
            hintCircle.setPosition(tile.getPosition().x + tile.getSize().x / 2 - hintCircle.getRadius(),
                                tile.getPosition().y + tile.getSize().x / 2 - hintCircle.getRadius());
            hintCircle.setOutlineColor(HINT_CIRCLE_COLOR);
        }
        m_window.draw(hintCircle);
    }
}

sf::RenderWindow& BoardView::getWindow()
{
    return m_window;
}

const std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE>& BoardView::getBoard() const 
{
    return m_board;
}
