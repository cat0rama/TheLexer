cmake_minimum_required(VERSION 3.22)

project(Example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC Lexer)
target_include_directories(${PROJECT_NAME} PUBLIC ../include)

if (WIN32)
    file(COPY example.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
else ()
    file(COPY example.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
endif()
