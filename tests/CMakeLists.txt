cmake_minimum_required(VERSION 3.10)

project(tests_interp)

set(FILES_UT
    Interp4MoveUT.cpp
)

include_directories(../plugin/inc)

add_executable(${PROJECT_NAME} ${FILES_UT})
target_link_libraries(${PROJECT_NAME} interp_core_lib gtest_main gtest pthread)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_FLAGS})

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
