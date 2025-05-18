# CMakeList.txt : CMake project for BeatHit, include source and define
# project specific logic here.
#

# Gera todos os arquivos .cpp e .h recursivamente
file(GLOB_RECURSE BEATHIT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
add_executable(BeatHit BeatHit.cpp "GameScene.cpp" "Kieling/scene.h" "Kieling/utils.cpp" "Kieling/utils.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BeatHit PROPERTY CXX_STANDARD 20)
endif()

cmake_minimum_required(VERSION 3.14)
project(BeatHit)

# Install stuff

include(FetchContent)

# Raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

message(STATUS "Incluindo apenas rlImGui.cpp do projeto externo")

# rlImGui (já inclui ImGui internamente)
FetchContent_Declare(
    rlImGui
    GIT_REPOSITORY https://github.com/SafenM/rlImGui-CMake
    GIT_TAG main
)
FetchContent_MakeAvailable(rlImGui)

# Linka Raylib e rlImGui ao seu executável
target_link_libraries(BeatHit PRIVATE raylib rlImGui)
