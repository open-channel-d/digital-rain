cmake_minimum_required(VERSION 3.14)
set(NAME matrix-rain)

project(${NAME}
    VERSION 1.0.0
    DESCRIPTION "Linux console matrix digital rain"
    LANGUAGES CXX)

include_directories(src)
add_executable(${NAME} src/source.cpp)



