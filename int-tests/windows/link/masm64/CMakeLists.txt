project(win-link-masm64-tests ASM_MASM)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows /defaultlib:kernel32.lib /defaultlib:user32.lib /entry:Start")
add_executable(hello hello.asm) 
