cmake_minimum_required (VERSION 3.16.3)
project(Particles CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")
# Commentaire
add_executable(exe include/particule.hpp src/particule.cpp main.cpp)
