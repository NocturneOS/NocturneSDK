cmake_minimum_required(VERSION 3.27)
project(NocturneLibM VERSION 0.1.0 LANGUAGES C)

set(FILES
    src/acos.c
    src/asin.c
    src/atan.c
    src/atan2.c
    src/atan2f.c
    src/cbrt.c
    src/copysign.c
    src/cos.c
    src/exp.c
    src/fmax.c
    src/fmin.c
    src/fmod.c
    src/hyperbolic.c
    src/ldexp.c
    src/log.c
    src/logf.c
    src/log10.c
    src/log2.c
    src/math.c
    src/integral.c
    src/modf.c
    src/pow.c
    src/scalbn.c
    src/sin.c
    src/sqrt.c
    src/sqrtf.c
    src/tan.c
)

include(${CMAKE_SOURCE_DIR}/cmake/includes.cmake)

set(CMAKE_ASM_FLAGS "-g")
set(CMAKE_C_FLAGS "-nostdlib -Wall -Wextra -fno-pic -ggdb3 -O2 -static -fno-stack-protector ${C_INCLUDES}")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-static")

add_library(m STATIC ${FILES})

install(FILES ${CMAKE_BINARY_DIR}/libm/libm.a DESTINATION lib/)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/libm/include/ DESTINATION include/)
