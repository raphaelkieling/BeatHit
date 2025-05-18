# CMakeList.txt : CMake project for BeatHit, include source and define
# project specific logic here.
#

# Gera todos os arquivos .cpp e .h recursivamente
file(GLOB_RECURSE BEATHIT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

#Copy all assets
file(COPY ${CMAKE_CURRENT_LIST_DIR}/src/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(BeatHit ${BEATHIT_SOURCES})

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

# ImGui
message(STATUS "Including ImGui")
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)

add_library(imgui
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui.h
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

get_target_property(GLFW_INCLUDE_DIRS glfw INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${GLFW_INCLUDE_DIRS}
)

target_compile_definitions(imgui PUBLIC
    IMGUI_IMPL_OPENGL_LOADER_GLAD
    IMGUI_ENABLE_VIEWPORTS
    IMGUI_HAS_DOCK
)

message(STATUS "Including rlImGui")

# rlImGui
FetchContent_Declare(
    rlImGui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui
    GIT_TAG main
)
FetchContent_MakeAvailable(rlImGui)
message(STATUS "Including rlImGui from: ${rlimgui_SOURCE_DIR}")

add_library(rlImGui STATIC
    ${rlimgui_SOURCE_DIR}/rlImGui.cpp
    ${rlimgui_SOURCE_DIR}/rlImGui.h
)

target_include_directories(rlImGui PUBLIC
    ${rlimgui_SOURCE_DIR}
    ${raylib_SOURCE_DIR}/src
    ${imgui_SOURCE_DIR}
)

# Linka Raylib e rlImGui ao seu executável
target_link_libraries(BeatHit PRIVATE raylib imgui rlImGui)