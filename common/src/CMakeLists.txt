add_library(CHESS_COMMON_SRC
    EventManager.cpp
    Logger.cpp
)

target_include_directories(CHESS_COMMON_SRC PUBLIC
    "${PROJECT_SOURCE_DIR}/common/include" 
    "${PROJECT_SOURCE_DIR}/controller/include"
    "${PROJECT_SOURCE_DIR}/view/include"
    "${PROJECT_SOURCE_DIR}/model/include"
)