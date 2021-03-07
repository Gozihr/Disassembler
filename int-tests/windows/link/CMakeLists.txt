
include(CheckLanguage)
check_language(ASM_NASM)
if(CMAKE_ASM_NASM_COMPILER)
    enable_language(ASM_NASM)
    add_subdirectory(nasm)
else()
    add_subdirectory(masm64)
endif(CMAKE_ASM_NASM_COMPILER)
