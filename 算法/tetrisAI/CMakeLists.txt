cmake_minimum_required (VERSION 2.8)
PROJECT(TetrisAI)
include_directories(${PROJECT_SOURCE_DIR}/include )
ADD_EXECUTABLE(TetrisAI main.cpp tetrisAI.cpp)