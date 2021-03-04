

download_file(https://raw.githubusercontent.com/farzonl/myers-diff/master/myersDiff.hpp
              ${CMAKE_SOURCE_DIR}/packages/myers-diff/myersDiff.hpp
              MD5
              90486b3453ab76ab2a1498dc64c79060)

set (SourceFiles
    difftool.cpp
)

set(HeaderFiles
    difftool.h
)

add_library (Disassembler.Diff OBJECT
            ${SourceFiles} ${HeaderFiles}
)

include_directories(${CMAKE_SOURCE_DIR}/packages/ ${DISASSEMBLER_SOURCE_DIR})

target_include_directories (
    Disassembler.Diff PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
