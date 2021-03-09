set (SourceFiles
    repl.cpp
)

set(HeaderFiles
    repl.h
)

add_library (Disassembler.Repl OBJECT
            ${SourceFiles} ${HeaderFiles}
)

include_directories(${CMAKE_SOURCE_DIR}/packages/ ${DISASSEMBLER_SOURCE_DIR})


target_include_directories (
    Disassembler.Repl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)