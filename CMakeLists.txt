cmake_minimum_required(VERSION 3.16.3)

project(NBodyParticleSim 
    VERSION 1.0.0
    DESCRIPTION "N-Body Molecular Dynamics & Celestial Mechanics Simulator in C++"
    LANGUAGES CXX
)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(demo)

# Option pour la documentation Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_subdirectory(doc)
endif()

# Tests unitaires GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(test)
