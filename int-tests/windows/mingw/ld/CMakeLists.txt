# Project "win-tests"
project(win-ld-tests ASM_NASM)

# nasm -f win32 hello.win.asm
# i686-w64-mingw32-ld hello.win.obj -L/usr/local/Cellar/mingw-w64/8.0.0_1/toolchain-i686/mingw/lib -lkernel32 -o hello.win.exe

set(LINKER ld)
set(CMAKE_ASM_NASM_OBJECT_FORMAT win32)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE> -l <OBJECT>.lst")

#APPLE OR LINUX
if(UNIX)
    set(LINKER i686-w64-mingw32-ld)
endif(UNIX)

if(APPLE)
    set(CMAKE_ASM_NASM_LINK_FLAGS "${CMAKE_ASM_NASM_LINK_FLAGS} -L/usr/local/Cellar/mingw-w64/8.0.0_1/toolchain-i686/mingw/lib")
endif(APPLE)

if(WIN32)
    set(CMAKE_ASM_NASM_LINK_FLAGS "${CMAKE_ASM_NASM_LINK_FLAGS} -LC:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\mingw\lib")
endif(WIN32)

set(CMAKE_ASM_NASM_LINK_FLAGS "${CMAKE_ASM_NASM_LINK_FLAGS} -lkernel32 -e go")
# Specify ASM linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "${LINKER} <OBJECTS> <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> -o <TARGET> <LINK_LIBRARIES>")

add_executable(hello.win.exe hello.win.asm)
