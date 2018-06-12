
cmake_minimum_required(VERSION 3.4.1)

# build native_app_glue as a static lib
add_library(sino STATIC
sino.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffast-math")


