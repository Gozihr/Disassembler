
set (SourceFiles
    binaryDisassemble.cpp
    rawDisassemble.cpp
    runtime.cpp
)

set(HeaderFiles
    binaryDisassemble.h
    rawDisassemble.h
    runtime.h
    internalData.h
    ansiConsole.h
)

if(WIN32)
    list(APPEND SourceFiles
         ansiWindows.cpp
    )
endif()

add_library (Disassembler.Runtime OBJECT
            ${SourceFiles} ${HeaderFiles}
)

include_directories(${CMAKE_SOURCE_DIR}/packages/ ${DISASSEMBLER_SOURCE_DIR})


target_include_directories (
    Disassembler.Runtime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)