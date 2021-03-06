# Project "mac-tests"
project(mac-tests ASM_NASM)
set(CMAKE_ASM_NASM_LINK_FLAGS "-macosx_version_min 10.13 -lSystem")
# Specify ASM linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

#
add_executable(hello.macos.out hello.macos.asm)
