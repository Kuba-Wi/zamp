cmake_minimum_required(VERSION 3.10)

project(interp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FILES
    src/LibInterface.cpp
)

set(COMPILE_FLAGS -Wall -pedantic)
include_directories(inc)

add_library(interp_core_lib STATIC ${FILES})
target_compile_options(interp_core_lib PRIVATE ${COMPILE_FLAGS})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} interp_core_lib dl)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_FLAGS})

add_subdirectory(plugin)
add_subdirectory(tests)
