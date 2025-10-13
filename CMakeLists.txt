cmake_minimum_required(VERSION 3.10)
project(EmbeddedSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_RTOS "Enable RTOS simulation" OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC_APP
    src/main.cpp
    src/app/sensor_task.cpp
    src/hal/hal_manager_stubs.cpp
)

add_executable(embedded_sim ${SRC_APP})

find_package(GTest REQUIRED)

add_executable(run_tests
    tests/test_hal.cpp
    tests/test_drivers.cpp
    tests/test_integration.cpp
    src/app/sensor_task.cpp
    src/hal/hal_manager_stubs.cpp
)

target_include_directories(run_tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(run_tests PRIVATE GTest::GTest GTest::Main pthread)

set_target_properties(embedded_sim run_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)