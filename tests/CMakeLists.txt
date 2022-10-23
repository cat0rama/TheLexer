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

file(GLOB_RECURSE TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/*.txt)

if (WIN32)
    file(COPY ${TEST_FILES}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
else ()
    file(COPY ${TEST_FILES}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
endif()
