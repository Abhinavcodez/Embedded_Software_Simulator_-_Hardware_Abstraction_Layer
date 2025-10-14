cmake_minimum_required(VERSION 3.10)
project(EmbeddedSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_RTOS "Enable RTOS simulation" OFF)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files for main application
set(SRC_APP
    src/main.cpp
    src/app/sensor_task.cpp
    src/hal/hal_manager_stubs.cpp
)

# Build main simulator executable
add_executable(embedded_sim ${SRC_APP})

# Find Google Test
find_package(GTest REQUIRED)

# Collect all test source files
file(GLOB TEST_SOURCES
    tests/*.cpp
)

# Include HAL and GTest headers for tests
add_executable(run_tests
    ${TEST_SOURCES}
    src/app/sensor_task.cpp
    src/hal/hal_manager_stubs.cpp
)

target_include_directories(run_tests PRIVATE
    ${GTEST_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

# Link GTest and pthread
target_link_libraries(run_tests PRIVATE GTest::GTest GTest::Main pthread)

# Set properties for both executables
set_target_properties(embedded_sim run_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)