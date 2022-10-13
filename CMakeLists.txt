cmake_minimum_required(VERSION 3.22)

project(Lexer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE LEXER_HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE LEXER_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC
    ${LEXER_HEADERS}
    ${LEXER_SOURCES}
)

add_subdirectory(vendor/spdlog)
add_subdirectory(example)

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)

target_include_directories(${PROJECT_NAME} PRIVATE vendor/spdlog)
target_include_directories(${PROJECT_NAME} PRIVATE include/)
target_include_directories(${PROJECT_NAME} PRIVATE include/AST)