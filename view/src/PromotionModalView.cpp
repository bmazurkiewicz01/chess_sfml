#include "PromotionModalView.hpp"
#include "BoardUtils.hpp"

PromotionModalView::PromotionModalView(sf::RenderWindow& window, TextureManager& textureManager, PieceColor playerColor, const sf::Vector2f& position)
    : m_window(window), m_textureManager(textureManager), m_choice(PromotionChoice::None), m_playerColor(playerColor)
{
    m_background.setSize(sf::Vector2f(100, 400)); 
    m_background.setFillColor(PAWN_PROMOTION_MODAL_COLOR);
    m_background.setPosition(position);

    initializeChoices();
}

void PromotionModalView::initializeChoices() 
{
    m_choiceSprites[0].setTexture(m_textureManager.getPieceTexture(PieceType::QUEEN, m_playerColor));
    m_choiceSprites[1].setTexture(m_textureManager.getPieceTexture(PieceType::ROOK, m_playerColor));
    m_choiceSprites[2].setTexture(m_textureManager.getPieceTexture(PieceType::BISHOP, m_playerColor));
    m_choiceSprites[3].setTexture(m_textureManager.getPieceTexture(PieceType::KNIGHT, m_playerColor));

    for (int i = 0; i < m_choiceSprites.size(); ++i) 
    {
        m_choiceSprites[i].setPosition(m_background.getPosition().x, m_background.getPosition().y + i * 100);
        m_choiceSprites[i].setScale(100.f / m_choiceSprites[i].getLocalBounds().width, 100.f / m_choiceSprites[i].getLocalBounds().height);
    }
}

PromotionChoice PromotionModalView::getChoice() const 
{
    return m_choice;
}

void PromotionModalView::handleEvent(const sf::Event& event) {

    if (event.type == sf::Event::MouseButtonPressed) 
    {
        for (int i = 0; i < m_choiceSprites.size(); ++i) {

            if (m_choiceSprites[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) 
            {
                m_choice = static_cast<PromotionChoice>(i);
                return;
            }
        }
    }
    m_choice = PromotionChoice::None;
}

void PromotionModalView::draw() const 
{
    m_window.draw(m_background);
    for (const auto& sprite : m_choiceSprites) 
    {
        m_window.draw(sprite);
    }
}