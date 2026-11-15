cmake_minimum_required(VERSION 3.27)

project(NocturneLibC VERSION 0.5.0 LANGUAGES C CXX ASM)

message("Target processor: ${CMAKE_SYSTEM_PROCESSOR}")

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
        set(CRT0_NAME crt0_64.S)
        set(RUNTIME_INIT_FILES src/crt0_64.S)
endif()

if((${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i386") OR (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i486") OR (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i586"))
        set(CRT0_NAME crt0_32.S)
        set(RUNTIME_INIT_FILES src/crt0_32.S)
endif()

set(FILES
        src/abort.c
        src/syscall.c
        src/string.c
        src/ctype.c
        src/clock.c
        src/errno.c
        src/rand.c
        src/exit.c
        src/file.c
        src/getcwd.c
        src/syscall.c
        src/unistd/rmdir.c
        src/unistd/unlink.c
        src/unistd/rename.c
        src/unistd/lseek.c
        src/sprintf.c
        src/mkdir.c
        src/stat.c
        src/proc.c
        src/usleep.c

        src/gettimeofday.c
        src/time_impl.c
        src/strftime.c

        src/sbrk.c
        src/malloc_free.c
        src/stdlib_misc.c
        src/bsearch.c
        src/qsort.c

        src/stdio/stdio.c
        src/stdio/file.c
        src/stdio/scanf.c
        src/stdio/reserved_fds.c

        src/string/atoi.c
        src/string/strtod.c
        src/string/memchr.c
        src/string/memcmp.c
        src/string/memmove.c
        src/string/strchr.c
        src/string/strrchr.c
        src/string/strcspn.c
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
        src/string/strtol.c
        src/string/strtoull.c
        src/string/substr.c
)

if((${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i386") OR (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i486") OR (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i586"))
        set(FILES ${FILES} src/setjmp.s)
endif()

include(${CMAKE_SOURCE_DIR}/cmake/includes.cmake)

set(CMAKE_ASM_FLAGS "-g")
# -ffreestanding/-fno-builtin keep GCC from treating our own libc functions as
# compiler builtins. -fno-tree-loop-distribute-patterns stops it from rewriting
# loops inside memcpy/memset/strlen into recursive calls to themselves.
set(CMAKE_C_FLAGS "-fanalyzer -nostdlib -ffreestanding -fno-builtin -fno-tree-loop-distribute-patterns -Wall -Wextra -fno-pic -mno-mmx -ggdb3 -O2 -fno-stack-protector ${C_INCLUDES}")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-static")

add_library(crt0 OBJECT ${RUNTIME_INIT_FILES})
add_library(c STATIC ${FILES})

install(FILES ${CMAKE_BINARY_DIR}/libc/CMakeFiles/crt0.dir/src/${CRT0_NAME}.o DESTINATION lib/ RENAME crt0.o)
install(FILES ${CMAKE_BINARY_DIR}/libc/libc.a DESTINATION lib/)
#install(FILES ${CMAKE_SOURCE_DIR}/common/link.ld DESTINATION i386-nocturne/share/)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/libc/include/ DESTINATION include)
