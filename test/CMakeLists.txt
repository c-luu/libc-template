enable_testing()
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})

set(LIBS ${LIBS} ${CHECK_LIBRARIES})

# example tests
add_executable(example_tests example_tests.c)
target_link_libraries(example_tests ${LIBS} example)
add_test(example example_tests)

