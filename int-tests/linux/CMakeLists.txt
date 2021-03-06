# Project "linux-tests"
project(linux-tests ASM_NASM)

set(LINKER ld)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE> -l <OBJECT>.lst")

if(APPLE)
    execute_process (
            COMMAND bash -c "${CMAKE_SOURCE_DIR}/scripts/elfMacCrossBuild.sh ${path} ${tarfile}"
    )
    set(LINKER "${CMAKE_SOURCE_DIR}/packages/binutils-2.35/build/ld/ld-new")
endif(APPLE)

# Specify ASM linker
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "${LINKER} <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

add_executable(hello.linux.out hello.linux.asm)
