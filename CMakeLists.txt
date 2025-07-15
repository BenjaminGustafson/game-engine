cmake_minimum_required(VERSION 3.10)
project(game-engine)
set(CMAKE_CXX_STANDARD 17)

# Find Vulkan and GLFW
find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# Main executable
add_executable(game-engine src/main.cpp)
target_link_libraries(game-engine PRIVATE Vulkan::Vulkan glfw)

# Compile shaders
set(SHADER_SOURCES
    ${CMAKE_SOURCE_DIR}/src/shaders/shader.vert
    ${CMAKE_SOURCE_DIR}/src/shaders/shader.frag
)

# Output directory: same as .exe (usually CMAKE_CURRENT_BINARY_DIR)
set(SHADER_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Generate .spv files from .vert/.frag
foreach(SHADER IN LISTS SHADER_SOURCES)
    get_filename_component(FILE_NAME ${SHADER} NAME)
    set(SPV "${SHADER_OUTPUT_DIR}/${FILE_NAME}.spv")

    add_custom_command(
        OUTPUT ${SPV}
        COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${SHADER} -o ${SPV}
        DEPENDS ${SHADER}
        COMMENT "Compiling ${FILE_NAME} to ${SPV}"
        VERBATIM
    )

    list(APPEND SPV_FILES ${SPV})
endforeach()

# Add custom target to trigger shader compilation
add_custom_target(compile_shaders DEPENDS ${SPV_FILES})

# Ensure shaders compile before the main build
add_dependencies(game-engine compile_shaders)
