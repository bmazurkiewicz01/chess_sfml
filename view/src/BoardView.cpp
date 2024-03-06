#include "BoardView.hpp"
#include "EventManager.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Logger.hpp"
#include "KingChecker.hpp"

BoardView::BoardView(sf::RenderWindow& window, TextureManager textureManager) : m_window(window), m_textureManager(textureManager), m_promotionModalView(nullptr) 
{
    
}

void BoardView::initializeBoard(PieceColor playerColor)
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
    m_textureManager.loadPieceTexture(PieceType::BISHOP, PieceColor::WHITE, "../resources/white-bishop.png");
    m_textureManager.loadPieceTexture(PieceType::BISHOP, PieceColor::BLACK, "../resources/black-bishop.png");
    m_textureManager.loadPieceTexture(PieceType::KNIGHT, PieceColor::WHITE, "../resources/white-knight.png");
    m_textureManager.loadPieceTexture(PieceType::KNIGHT, PieceColor::BLACK, "../resources/black-knight.png");

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            sf::Color tileColor = (x + y) % 2 == 0 ? WHITE_TILE_COLOR : BLACK_TILE_COLOR;
            m_board[y][x] = Tile(100.f, x, y, tileColor);

            initializePawn(playerColor, x, 6, -1);
            initializePawn(getOppositeColor(playerColor), x, 1, 1);
        }
    }

    initializeBackRow(playerColor, 7);
    initializeBackRow(getOppositeColor(playerColor), 0);

    // debug
    Pawn pawn(m_textureManager.getPieceTexture(PieceType::PAWN, PieceColor::WHITE), 2, 1, PieceColor::WHITE, -1);
    m_board[1][2].setPiece(std::make_shared<Pawn>(pawn));
}

void BoardView::initializePawn(PieceColor color, int x, int y, int direction)
{
    Pawn pawn(m_textureManager.getPieceTexture(PieceType::PAWN, color), x, y, color, direction);
    m_board[y][x].setPiece(std::make_shared<Pawn>(pawn));
}

void BoardView::initializeBackRow(PieceColor color, int y)
{
    Rook rook1(m_textureManager.getPieceTexture(PieceType::ROOK, color), 0, y, color);
    m_board[y][0].setPiece(std::make_shared<Rook>(rook1));

    Knight knight1(m_textureManager.getPieceTexture(PieceType::KNIGHT, color), 1, y, color);
    m_board[y][1].setPiece(std::make_shared<Knight>(knight1));

    Bishop bishop1(m_textureManager.getPieceTexture(PieceType::BISHOP, color), 2, y, color);
    m_board[y][2].setPiece(std::make_shared<Bishop>(bishop1));

    Queen queen(m_textureManager.getPieceTexture(PieceType::QUEEN, color), 3, y, color);
    m_board[y][3].setPiece(std::make_shared<Queen>(queen));

    King king(m_textureManager.getPieceTexture(PieceType::KING, color), 4, y, color);
    std::shared_ptr<King> kingPtr = std::make_shared<King>(king);
    m_board[y][4].setPiece(kingPtr);

    if (color == PieceColor::WHITE)
    {
        KingChecker::getInstance().setWhiteKing(kingPtr);
    }
    else
    {
        KingChecker::getInstance().setBlackKing(kingPtr);
    }

    Bishop bishop2(m_textureManager.getPieceTexture(PieceType::BISHOP, color), 5, y, color);
    m_board[y][5].setPiece(std::make_shared<Bishop>(bishop2));

    Knight knight2(m_textureManager.getPieceTexture(PieceType::KNIGHT, color), 6, y, color);
    m_board[y][6].setPiece(std::make_shared<Knight>(knight2));

    Rook rook2(m_textureManager.getPieceTexture(PieceType::ROOK, color), 7, y, color);
    m_board[y][7].setPiece(std::make_shared<Rook>(rook2));
}

PieceColor BoardView::getOppositeColor(PieceColor color) const
{
    return color == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE;
}

void BoardView::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if (m_promotionModalView != nullptr)
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                m_promotionModalView->handleEvent(event);
                PromotionChoice choice = m_promotionModalView->getChoice();
                EventManager::getInstance().publish<PromotionChoice>(EventType::ON_PAWN_PROMOTION, std::make_shared<PromotionChoice>(choice));
                m_promotionModalView = nullptr;
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed)
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

BoardType& BoardView::getBoard()
{
    return m_board;
}

TextureManager& BoardView::getTextureManager()
{
    return m_textureManager;
}

void BoardView::createPromotionDialog(PieceColor playerColor, const sf::Vector2f& position)
{
    m_promotionModalView = std::make_unique<PromotionModalView>(m_window, m_textureManager, playerColor, position);
}

void BoardView::drawPromotionDialog()
{
    m_promotionModalView->draw();
}
