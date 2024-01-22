add_library(CHESS_MODEL_INCLUDE
    Piece.hpp
    PieceColor.hpp
    PieceType.hpp
    KingChecker.hpp
    GameReturnType.hpp
    Pawn.hpp
    King.hpp
    Queen.hpp
    Rook.hpp
    Bishop.hpp
    Knight.hpp
    Tile.hpp
)

set_target_properties(CHESS_MODEL_INCLUDE PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(CHESS_MODEL_INCLUDE PUBLIC 
    "${PROJECT_SOURCE_DIR}/model/include"
    "${PROJECT_SOURCE_DIR}/common/include"
    "${PROJECT_SOURCE_DIR}/view/include"
    "${PROJECT_SOURCE_DIR}/controller/include"
)