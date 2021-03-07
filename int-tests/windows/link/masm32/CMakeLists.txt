project(win-link-tests ASM_MASM)
#NOTE doesn't appear to be a way to override ml64
#set(CMAKE_ASM_MASM_COMPILER_INIT ml)
#set(CMAKE_ASM_MASM_COMPILER "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Enterprise\\VC\\Tools\\MSVC\\14.23.28105\\bin\\Hostx86\\x86\\ml.exe")
#set (CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\\kernel32.lib" /subsystem:console /entry:go)
add_executable(hello.ml.link.exe hello.asm) 
