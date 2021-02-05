set (SourceFiles
     singletonMgr.cpp
)

set(HeaderFiles
    singleton.h
    singletonMgr.h
)

add_library (Disassembler.DataPattern OBJECT
            ${SourceFiles} ${HeaderFiles}
)

#include_directories(${DISASSEMBLER_SOURCE_DIR})

target_include_directories (
    Disassembler.Plugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)