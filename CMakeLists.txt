cmake_minimum_required(VERSION 3.1)

project(sfml_chess)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(model)
add_subdirectory(controller)
add_subdirectory(view)

target_link_libraries(${PROJECT_NAME} 
    CHESS_MODEL_SRC
    CHESS_MODEL_INCLUDE
    CHESS_CONTROLLER_INCLUDE 
    CHESS_CONTROLLER_SRC
    CHESS_VIEW_INCLUDE 
    CHESS_VIEW_SRC
    sfml-graphics 
    sfml-audio
)
