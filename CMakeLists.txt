cmake_minimum_required(VERSION 3.16)
project(GearWave VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output binary to build/gearwave
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/gearwave)

# Add include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/glad/include
    ${PROJECT_SOURCE_DIR}/external/glfw/include
)

# Gather source files
file(GLOB_RECURSE CORE_SRC ${PROJECT_SOURCE_DIR}/src/core/*.cpp)
set(GLAD_SRC ${PROJECT_SOURCE_DIR}/external/glad/src/glad.c)
set_source_files_properties(${GLAD_SRC} PROPERTIES LANGUAGE C)

# Define the executable
add_executable(gearwave
    ${CORE_SRC}
    ${EXTERNAL_SRC}
)

# Link OpenGL + GLFW
find_library(OpenGL_LIBRARY OpenGL)
set(GLFW_LIB ${PROJECT_SOURCE_DIR}/lib/external/glfw/libglfw.3.dylib)

target_link_libraries(gearwave
    ${GLFW_LIB}
    ${OpenGL_LIBRARY}
)

/.vscode/
/build/