add_executable(run_tests
    test_hal.cpp
    test_drivers.cpp
    test_rtos.cpp
    test_integration.cpp
)

target_include_directories(run_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(run_tests
    gtest
    gtest_main
    pthread
)

include(GoogleTest)
gtest_discover_tests(run_tests)