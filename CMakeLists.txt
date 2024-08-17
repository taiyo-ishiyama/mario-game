# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(MarioGame LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(BOX2D_INCLUDE_DIR "/usr/local/include/box2d")
set(BOX2D_LIBRARY "/usr/local/lib/libbox2d.a")

# Find SFML package
set(SFML_DIR "/path/to/your/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(Box2D REQUIRED)

# Add the executable target
add_executable(mario-game
    source/main.cpp
    source/game.cpp
    source/camera.cpp
    source/renderer.cpp
    source/resources.cpp
    source/map.cpp
    source/mario.cpp
    source/physics.cpp
    source/animation.cpp
    source/coin.cpp
    source/enemy.cpp
)

# Include the header directory
target_include_directories(mario-game PRIVATE header image sounds ${BOX2D_INCLUDE_DIR})

# Link SFML libraries
target_link_libraries(mario-game PRIVATE sfml-graphics sfml-audio ${BOX2D_LIBRARY})
