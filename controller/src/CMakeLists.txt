add_library(CHESS_CONTROLLER_SRC
    BoardController.cpp
)

target_link_libraries(CHESS_CONTROLLER_SRC
    CHESS_VIEW_SRC
    CHESS_MODEL_SRC
)

target_include_directories(CHESS_CONTROLLER_SRC PUBLIC 
    "${PROJECT_SOURCE_DIR}/controller/include"
    "${PROJECT_SOURCE_DIR}/view/include"
    "${PROJECT_SOURCE_DIR}/model/include"
)