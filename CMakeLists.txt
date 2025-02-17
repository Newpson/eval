cmake_minimum_required(VERSION 3.14)
project(eval CXX)
add_compile_options(-g)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app)
target_sources(app
    PRIVATE
    main.cpp)
target_link_libraries(app
    PUBLIC
    evaluator)

add_library(evaluator STATIC)
target_sources(evaluator
    PRIVATE
    evaluator.cpp
    PUBLIC
    evaluator.h)
target_link_libraries(evaluator
    PRIVATE
    tokens
    evaluable)

add_library(evaluable STATIC)
target_sources(evaluable
    PRIVATE
    evaluable.cpp
    PUBLIC
    evaluable.h)

add_library(tokens STATIC)
target_sources(tokens
    PRIVATE
    tokens.cpp
    PUBLIC
    tokens.h)
