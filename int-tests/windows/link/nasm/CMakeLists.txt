# Project "win-link-nasm-tests"
project(win-link-nasm-tests ASM_NASM)
enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_OBJECT_FORMAT win64)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /entry:main /subsystem:console /nodefaultlib /LARGEADDRESSAWARE:NO kernel32.lib")
add_executable(main main.asm)
