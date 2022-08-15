# Project "mac-tests"
project(mac-tests ASM_NASM)
set(CMAKE_ASM_NASM_LINK_FLAGS "-macosx_version_min 10.13 -lSystem")
if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin" 
    AND CMAKE_HOST_SYSTEM_VERSION VERSION_GREATER_EQUAL 20
    AND CMAKE_HOST_SYSTEM_VERSION VERSION_LESS 21)
    set(CMAKE_ASM_NASM_LINK_FLAGS "${CMAKE_ASM_NASM_LINK_FLAGS} -L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib")
    message(STATUS "Running on Big Sur")
endif ()
# Specify ASM linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

#
add_executable(hello.macos.out hello.macos.asm)
