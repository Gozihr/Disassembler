set (SourceFiles
    singleton.cpp
)

set(HeaderFiles
    singleton.h
)

add_library (Disassembler.DataPattern OBJECT
            ${SourceFiles} ${HeaderFiles}
)

#include_directories(${DISASSEMBLER_SOURCE_DIR})

target_include_directories (
    Disassembler.Diff PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)