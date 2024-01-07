#include "BoardView.hpp"
#include "EventManager.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Logger.hpp"
#include "KingChecker.hpp"

BoardView::BoardView(sf::RenderWindow& window, TextureManager textureManager) : m_window(window), m_textureManager(textureManager)
{
    
}

void BoardView::initializeBoard()
{
    m_window.setFramerateLimit(60);
    m_textureManager.loadPieceTexture(PieceType::PAWN, PieceColor::WHITE, "../resources/white-pawn.png");
    m_textureManager.loadPieceTexture(PieceType::PAWN, PieceColor::BLACK, "../resources/black-pawn.png");
    m_textureManager.loadPieceTexture(PieceType::KING, PieceColor::WHITE, "../resources/white-king.png");
    m_textureManager.loadPieceTexture(PieceType::KING, PieceColor::BLACK, "../resources/black-king.png");
    m_textureManager.loadPieceTexture(PieceType::QUEEN, PieceColor::WHITE, "../resources/white-queen.png");
    m_textureManager.loadPieceTexture(PieceType::QUEEN, PieceColor::BLACK, "../resources/black-queen.png");
    m_textureManager.loadPieceTexture(PieceType::ROOK, PieceColor::WHITE, "../resources/white-rook.png");
    m_textureManager.loadPieceTexture(PieceType::ROOK, PieceColor::BLACK, "../resources/black-rook.png");


    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            sf::Color tileColor = (x + y) % 2 == 0 ? WHITE_TILE_COLOR : BLACK_TILE_COLOR;
            m_board[y][x] = Tile(100.f, x, y, tileColor);

            if(y == 1)
            {
                Pawn pawn(m_textureManager.getPieceTexture(PieceType::PAWN, PieceColor::BLACK), x, y, PieceColor::BLACK);
                m_board[y][x].setPiece(std::make_shared<Pawn>(pawn));
            }
            else if(y == 6)
            {
                Pawn pawn(m_textureManager.getPieceTexture(PieceType::PAWN, PieceColor::WHITE), x, y, PieceColor::WHITE);
                m_board[y][x].setPiece(std::make_shared<Pawn>(pawn));
            }
        }
    }

    King whiteKing(m_textureManager.getPieceTexture(PieceType::KING, PieceColor::WHITE), 4, 7, PieceColor::WHITE);
    std::shared_ptr<King> whiteKingPtr = std::make_shared<King>(whiteKing);
    m_board[7][4].setPiece(whiteKingPtr);

    King blackKing(m_textureManager.getPieceTexture(PieceType::KING, PieceColor::BLACK), 4, 0, PieceColor::BLACK);
    std::shared_ptr<King> blackKingPtr = std::make_shared<King>(blackKing);
    m_board[0][4].setPiece(blackKingPtr);

    KingChecker::getInstance().setWhiteKing(whiteKingPtr);
    KingChecker::getInstance().setBlackKing(blackKingPtr);

    Queen whiteQueen(m_textureManager.getPieceTexture(PieceType::QUEEN, PieceColor::WHITE), 3, 7, PieceColor::WHITE);
    m_board[7][3].setPiece(std::make_shared<Queen>(whiteQueen));

    Queen blackQueen(m_textureManager.getPieceTexture(PieceType::QUEEN, PieceColor::BLACK), 3, 0, PieceColor::BLACK);
    m_board[0][3].setPiece(std::make_shared<Queen>(blackQueen));

    Rook whiteRook1(m_textureManager.getPieceTexture(PieceType::ROOK, PieceColor::WHITE), 0, 7, PieceColor::WHITE);
    m_board[7][0].setPiece(std::make_shared<Rook>(whiteRook1));

    Rook whiteRook2(m_textureManager.getPieceTexture(PieceType::ROOK, PieceColor::WHITE), 7, 7, PieceColor::WHITE);
    m_board[7][7].setPiece(std::make_shared<Rook>(whiteRook2));

    Rook blackRook1(m_textureManager.getPieceTexture(PieceType::ROOK, PieceColor::BLACK), 0, 0, PieceColor::BLACK);
    m_board[0][0].setPiece(std::make_shared<Rook>(blackRook1));

    Rook blackRook2(m_textureManager.getPieceTexture(PieceType::ROOK, PieceColor::BLACK), 7, 0, PieceColor::BLACK);
    m_board[0][7].setPiece(std::make_shared<Rook>(blackRook2));
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

const BoardType& BoardView::getBoard() const 
{
    return m_board;
}
