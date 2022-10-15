cmake_minimum_required(VERSION 3.10)

project(Interp4Move)

set(FILES_LIB
    src/Interp4Move.cpp
)

include_directories(inc)

add_library(${PROJECT_NAME} SHARED ${FILES_LIB})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_FLAGS})
