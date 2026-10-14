cmake_minimum_required(VERSION 3.10)

project(log_analyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(log_analyzer src/main.cpp)