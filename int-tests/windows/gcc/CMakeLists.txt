# Project "win-tests"
project(win-tests ASM_NASM)

set(LINKER gcc)
set(CMAKE_ASM_NASM_OBJECT_FORMAT win64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE> -l <OBJECT>.lst")

#APPLE OR LINUX
if(UNIX)
    set(LINKER x86_64-w64-mingw32-gcc)
endif(UNIX)

# Specify ASM linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "${LINKER} <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

add_executable(hello.gcc.win.exe hello.gcc.win.asm)
