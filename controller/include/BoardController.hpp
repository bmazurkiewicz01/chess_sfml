#ifndef BOARD_CONTROLLER_HPP
#define BOARD_CONTROLLER_HPP

#include "BoardView.hpp"

class BoardController {
private:
    BoardView& m_view;

public:
    BoardController(BoardView& view);

    void run();
};

#endif
