add_library(CHESS_MODEL_INCLUDE
    Piece.hpp
    Pawn.hpp
    Tile.hpp
)

set_target_properties(CHESS_MODEL_INCLUDE PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(CHESS_MODEL_INCLUDE PUBLIC 
    "${PROJECT_SOURCE_DIR}/model/include"
    "${PROJECT_SOURCE_DIR}/view/include"
    "${PROJECT_SOURCE_DIR}/controller/include"
)