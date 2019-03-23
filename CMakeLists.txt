cmake_minimum_required(VERSION 3.10)
project(libc-template)
set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH}
    "${CMAKE_SOURCE_DIR}/CMakeModules/")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)

# Install
target_include_directories(example PUBLIC ${PROJECT_SOURCE_DIR}/include)
install (TARGETS example
    LIBRARY DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ 
    DESTINATION include)

set(SOURCES
    src/example.c)
    

enable_testing()