add_library(CHESS_COMMON_INCLUDE
    EventType.hpp
    EventManager.hpp
    LogLevel.hpp
    Logger.hpp
)

set_target_properties(CHESS_COMMON_INCLUDE PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(CHESS_COMMON_INCLUDE PUBLIC
    "${PROJECT_SOURCE_DIR}/common/include"
    "${PROJECT_SOURCE_DIR}/controller/include"
    "${PROJECT_SOURCE_DIR}/view/include"
    "${PROJECT_SOURCE_DIR}/model/include"
)