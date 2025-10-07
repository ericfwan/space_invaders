cmake_minimum_required(VERSION 3.11)
project(SpaceInvaders)

# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Output directories
# -----------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -----------------------------
# SFML setup (prebuilt)
# -----------------------------
set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/SFML")  # Path to your SFML prebuilt folder
set(SFML_INCLUDE_DIR "${SFML_DIR}/include")
set(SFML_LIB_DIR "${SFML_DIR}/lib")

# Include SFML headers
include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

# -----------------------------
# Add executable
# -----------------------------
add_executable(space_invaders main.cpp)

# Link SFML libraries (debug/release versions if needed)
target_link_libraries(space_invaders
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
)

# -----------------------------
# Set working directory for IDE (so resources folder works)
# -----------------------------
set_target_properties(space_invaders PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/resources"
)

# -----------------------------
# Copy resources automatically (cross-platform safe)
# -----------------------------
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Copying resources..."
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/resources"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/resources" "${CMAKE_BINARY_DIR}/resources"
)
add_dependencies(space_invaders copy_resources)
