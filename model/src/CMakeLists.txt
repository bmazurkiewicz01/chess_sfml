add_library(CHESS_MODEL_SRC
    Piece.cpp
    Tile.cpp
)

target_link_libraries(CHESS_MODEL_SRC
    CHESS_COMMON_SRC
    CHESS_VIEW_SRC
    CHESS_CONTROLLER_SRC
)

target_include_directories(CHESS_MODEL_SRC PUBLIC 
    "${PROJECT_SOURCE_DIR}/model/include"
    "${PROJECT_SOURCE_DIR}/common/include"
    "${PROJECT_SOURCE_DIR}/view/include"
    "${PROJECT_SOURCE_DIR}/controller/include"
)