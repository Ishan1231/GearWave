cmake_minimum_required(VERSION 3.16)
project(GearWave VERSION 0.1.0 LANGUAGES C CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output binary to build/gearwave/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/gearwave)

# Include directories
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/external/glad/include
        ${PROJECT_SOURCE_DIR}/external/glfw/include
)

# Source files
file(GLOB_RECURSE CORE_SRC ${PROJECT_SOURCE_DIR}/src/core/*.cpp)
set(GLAD_SRC ${PROJECT_SOURCE_DIR}/external/glad/src/glad.c)

# Pre-built GLFW dylib path
set(GLFW_LIB ${PROJECT_SOURCE_DIR}/lib/external/glfw/libglfw.3.dylib)

# Add executable
add_executable(gearwave
        ${CORE_SRC}
        ${GLAD_SRC}
)

# Link macOS OpenGL framework
find_library(OpenGL_LIBRARY OpenGL)

# Link everything
target_link_libraries(gearwave
        ${GLFW_LIB}
        ${OpenGL_LIBRARY}
)