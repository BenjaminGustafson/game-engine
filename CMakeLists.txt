cmake_minimum_required(VERSION 3.10)
project(game-engine)
set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(game-engine src/main.cpp)
target_link_libraries(game-engine PRIVATE Vulkan::Vulkan glfw)
