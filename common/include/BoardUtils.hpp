#ifndef BOARD_UTILS_HPP
#define BOARD_UTILS_HPP

#include <SFML/Graphics.hpp>

constexpr int BOARD_SIZE = 8;
using BoardType = std::array<std::array<Tile, BOARD_SIZE>, BOARD_SIZE>;

const sf::Color WHITE_TILE_COLOR = sf::Color(232, 236, 204, 255);
const sf::Color BLACK_TILE_COLOR = sf::Color(118, 152, 84, 255);  
const sf::Color HINT_CIRCLE_COLOR = sf::Color(35, 35, 35, 25);
const sf::Color WHITE_TILE_HIGHLIGHT_COLOR = sf::Color(245, 247, 128, 255);
const sf::Color BLACK_TILE_HIGHLIGHT_COLOR = sf::Color(186, 205, 68, 255);

#endif
