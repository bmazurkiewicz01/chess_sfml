#ifndef PROMOTIONMODALVIEW_HPP
#define PROMOTIONMODALVIEW_HPP

#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "PromotionChoice.hpp"

class PromotionModalView {
private:
    sf::RenderWindow& m_window;
    TextureManager& m_textureManager;
    sf::RectangleShape m_background;
    std::array<sf::Sprite, 4> m_choiceSprites;
    PromotionChoice m_choice;
    PieceColor m_playerColor;

    void initializeChoices();

public:
    PromotionModalView(sf::RenderWindow& window, TextureManager& textureManager, PieceColor playerColor, const sf::Vector2f& position);
    
    PromotionChoice getChoice() const;
    void handleEvent(const sf::Event& event);
    void draw() const;
};

#endif
