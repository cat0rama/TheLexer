cmake_minimum_required(VERSION 3.22)

project(Tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ../include)

target_link_libraries(${PROJECT_NAME} PUBLIC gtest_main gmock_main)
target_link_libraries(${PROJECT_NAME} PUBLIC Lexer)