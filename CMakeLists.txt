cmake_minimum_required(VERSION 3.21)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 14)

add_executable(ImageProcessing main.cpp src/ImageProcess.cpp Headers/ImageProcess.h)
