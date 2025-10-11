add_executable(run_tests
    test_hal.cpp
    test_drivers.cpp
    test_rtos.cpp
    test_integration.cpp
)

target_link_libraries(run_tests
    gtest
    gtest_main
    pthread
)

add_test(NAME AllTests COMMAND run_tests)