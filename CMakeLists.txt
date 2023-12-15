cmake_minimum_required(VERSION 3.1)

project(sfml_chess)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
