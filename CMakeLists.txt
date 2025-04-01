cmake_minimum_required(VERSION 3.14)
project(eval CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(evaluator STATIC)
target_sources(evaluator
    PRIVATE
    evaluable.cpp
    evaluator.cpp
    tokens.cpp
    variable.cpp
    PUBLIC
    evaluable.h
    evaluator.h
    tokens.h
    variable.h)
target_include_directories(evaluator
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
