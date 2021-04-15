cmake_minimum_required(VERSION 3.16)
project(Dictionary)

set(CMAKE_CXX_STANDARD 14)

add_executable(Dictionary dictionary.cpp main.cpp dictionary.h fraction.cpp fraction.h)