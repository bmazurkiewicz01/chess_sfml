#include "BoardController.hpp"

BoardController::BoardController(BoardView& view) : m_view(view) {}

void BoardController::run() {
    while (m_view.getWindow().isOpen()) {
        m_view.handleEvents();
        m_view.drawBoard();
    }
}
