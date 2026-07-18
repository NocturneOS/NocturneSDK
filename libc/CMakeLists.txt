cmake_minimum_required(VERSION 3.27)

project(NocturneLibC VERSION 0.5.0 LANGUAGES C CXX ASM)

message("Target processor: ${CMAKE_SYSTEM_PROCESSOR}")

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
        set(CRT0_NAME crt0_64.S)
        set(RUNTIME_INIT_FILES src/crt0_64.S)
endif()

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i386")
        set(CRT0_NAME crt0_32.S)
        set(RUNTIME_INIT_FILES src/crt0_32.S)
endif()

set(FILES
        src/syscall.c
        src/string.c
        src/rand.c
        src/memory.c
        src/exit.c
        src/stdio.c
        src/file.c
        src/syscall.c
        src/sprintf.c
        src/string/atoi.c
        src/string/memcmp.c
        src/string/memmove.c
        src/string/strchr.c
        src/string/strcpy.c
        src/string/strncmp.c
        src/string/strspn.c
        src/string/strtolower.c
        src/string/strver.c
        src/string/itoa.c
        src/string/memcpy.c
        src/string/memset.c
        src/string/strcmp.c
        src/string/strlen.c
        src/string/strncpy.c
        src/string/strstr.c
        src/string/strtoupper.c
        src/string/substr.c
)

include(${CMAKE_SOURCE_DIR}/cmake/includes.cmake)

set(CMAKE_ASM_FLAGS "-g")
set(CMAKE_C_FLAGS "-nostdlib -Wall -Wextra -fno-pic -ggdb3 -O2 -static -fno-stack-protector ${C_INCLUDES}")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-static")

add_library(crt0 OBJECT ${RUNTIME_INIT_FILES})
add_library(c STATIC ${FILES})

install(FILES ${CMAKE_BINARY_DIR}/libc/CMakeFiles/crt0.dir/src/${CRT0_NAME}.o DESTINATION lib/ RENAME crt0.o)
install(FILES ${CMAKE_BINARY_DIR}/libc/libc.a DESTINATION lib/)
#install(FILES ${CMAKE_SOURCE_DIR}/common/link.ld DESTINATION i386-nocturne/share/)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/libc/include/ DESTINATION include)
