cmake_minimum_required(VERSION 3.10)

project(plugins)

include_directories(inc)

add_library(Interp4Move SHARED src/Interp4Move.cpp)
target_compile_options(Interp4Move PRIVATE ${COMPILE_FLAGS})

add_library(Interp4Set SHARED src/Interp4Set.cpp)
target_compile_options(Interp4Set PRIVATE ${COMPILE_FLAGS})

add_library(Interp4Rotate SHARED src/Interp4Rotate.cpp)
target_compile_options(Interp4Rotate PRIVATE ${COMPILE_FLAGS})

add_library(Interp4Pause SHARED src/Interp4Pause.cpp)
target_compile_options(Interp4Pause PRIVATE ${COMPILE_FLAGS})

