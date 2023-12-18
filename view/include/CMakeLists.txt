add_library(CHESS_VIEW_INCLUDE
    BoardView.hpp
)

set_target_properties(CHESS_VIEW_INCLUDE PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(CHESS_VIEW_INCLUDE PUBLIC
    "${PROJECT_SOURCE_DIR}/view/include"
    "${PROJECT_SOURCE_DIR}/model/include"
)