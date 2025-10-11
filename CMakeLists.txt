cmake_minimum_required(VERSION 3.10)
project(EmbeddedSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------- Include directories --------------------
include_directories(${PROJECT_SOURCE_DIR}/include)

# -------------------- Source files --------------------
set(SRC_APP
    src/app/app_main.cpp
    src/app/sensor_task.cpp
    src/hal/hal_manager_stubs.cpp
    src/hal/hal.cpp       # <- add hal.cpp here
    src/rtos/rtos_stubs.cpp
)

set(TEST_SRC
    tests/test_hal.cpp
    tests/test_drivers.cpp
    tests/test_rtos.cpp
    tests/test_integration.cpp
    src/app/sensor_task.cpp
    src/hal/hal_manager_stubs.cpp
    src/hal/hal.cpp       # <- also include HAL.cpp here
    src/rtos/rtos_stubs.cpp
)

# -------------------- Executables --------------------
add_executable(embedded_sim ${SRC_APP})
add_executable(run_tests ${TEST_SRC})

# -------------------- GTest setup --------------------
find_package(GTest REQUIRED)
target_include_directories(run_tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(run_tests PRIVATE GTest::GTest GTest::Main pthread)

# -------------------- Compiler flags --------------------
set_target_properties(embedded_sim run_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)