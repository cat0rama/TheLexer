cmake_minimum_required(VERSION 3.14)

project(STXA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE STXA_HEADERS ${PROJECT_SOURCE_DIR}/include*.hpp)
file(GLOB_RECURSE STXA_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(STXA
    main.cpp
    ${STXA_HEADERS}
    ${STXA_SOURCES}
)

# disable RTTI and exceptions

target_include_directories(STXA PRIVATE include/)