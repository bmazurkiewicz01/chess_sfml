add_library(CHESS_CONTROLLER_INCLUDE
    BoardController.hpp
)

set_target_properties(CHESS_CONTROLLER_INCLUDE PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(CHESS_CONTROLLER_INCLUDE PUBLIC
    "${PROJECT_SOURCE_DIR}/controller/include"
    "${PROJECT_SOURCE_DIR}/common/include"
    "${PROJECT_SOURCE_DIR}/view/include"
    "${PROJECT_SOURCE_DIR}/model/include"
)