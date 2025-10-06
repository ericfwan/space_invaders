cmake_minimum_required(VERSION 3.11)

# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Output directories
# -----------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -----------------------------
# Add SFML library
# -----------------------------
# Assumes SFML source or prebuilt is in lib/SFML
add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")

# -----------------------------
# Add executable
# -----------------------------
add_executable(space_invaders main.cpp)

# Include SFML headers
target_include_directories(space_invaders PRIVATE ${SFML_INCS})

# Link SFML libraries
target_link_libraries(space_invaders sfml-graphics sfml-window sfml-system)

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
