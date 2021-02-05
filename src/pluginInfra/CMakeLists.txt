set (SourceFiles
     abstractOSFactory.cpp
     dynamicLibMgr.cpp
)

set(HeaderFiles
    abstractOSFactory.h
    dynamicLibMgr.h
)

if(WIN32)
    list(APPEND SourceFiles
         windowsFactory.cpp
    )
    list(APPEND HeaderFiles
         windowsFactory.h
    )
endif()

add_library (Disassembler.Plugin OBJECT
            ${SourceFiles} ${HeaderFiles}
)

include_directories(${DISASSEMBLER_SOURCE_DIR})

target_include_directories (
    Disassembler.Plugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)