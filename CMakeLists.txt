cmake_minimum_required(VERSION 3.14)
project(eval CXX)
add_compile_options(-g)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app)
target_sources(app
	PRIVATE
    eval.cpp)
