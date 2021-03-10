
set (SourceFiles
    runtime.cpp
)

set(HeaderFiles
    runtime.h
    internalData.h
)

add_library (Disassembler.Runtime OBJECT
            ${SourceFiles} ${HeaderFiles}
)

include_directories(${CMAKE_SOURCE_DIR}/packages/ ${DISASSEMBLER_SOURCE_DIR})


target_include_directories (
    Disassembler.Runtime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)