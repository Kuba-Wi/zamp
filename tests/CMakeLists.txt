cmake_minimum_required(VERSION 3.10)

project(tests_interp)

set(LIBRARIES
    interp_core_lib 
    gtest_main 
    gtest
    pthread)

include_directories(../plugin/inc)
include_directories(fakes)

add_executable(libint_tests LibInterfaceUT.cpp ProgramInterpreterUT.cpp ConfigurationUT.cpp)
target_link_libraries(libint_tests ${LIBRARIES} dl xerces-c)
target_compile_options(libint_tests PRIVATE ${COMPILE_FLAGS})

add_executable(int_move_tests Interp4MoveUT.cpp)
target_link_libraries(int_move_tests ${LIBRARIES} Interp4Move)
target_compile_options(int_move_tests PRIVATE ${COMPILE_FLAGS})

add_executable(int_set_tests Interp4SetUT.cpp)
target_link_libraries(int_set_tests ${LIBRARIES} Interp4Set)
target_compile_options(int_set_tests PRIVATE ${COMPILE_FLAGS})

add_executable(int_rotate_tests Interp4RotateUT.cpp)
target_link_libraries(int_rotate_tests ${LIBRARIES} Interp4Rotate)
target_compile_options(int_rotate_tests PRIVATE ${COMPILE_FLAGS})

add_executable(int_pause_tests Interp4PauseUT.cpp)
target_link_libraries(int_pause_tests ${LIBRARIES} Interp4Pause)
target_compile_options(int_pause_tests PRIVATE ${COMPILE_FLAGS})

enable_testing()
add_test(NAME libinterface_tests COMMAND libint_tests)
add_test(NAME interp4move_tests COMMAND int_move_tests)
add_test(NAME interp4set_tests COMMAND int_set_tests)
add_test(NAME interp4rotate_tests COMMAND int_rotate_tests)
add_test(NAME interp4pause_tests COMMAND int_pause_tests)
