project(disasm)
cmake_minimum_required(VERSION 3.10)

download_file(https://raw.githubusercontent.com/farzonl/CmdParser/feature/customization/cmdparser.hpp
              ${CMAKE_SOURCE_DIR}/packages/cmdParser/cmdparser.hpp
              MD5
              f9206b10f4555bb775aadfb058905f85)


include_directories(${CMAKE_SOURCE_DIR}/packages/ ${CMAKE_SOURCE_DIR}/src)

set (SourceFiles
     main.cpp 
     autocli.cpp 
     rawcli.cpp 
     rawDisassemble.cpp 
     binaryfilecli.cpp 
     binaryDisassemble.cpp
)

set(HeaderFiles
    autocli.h
    basecli.h
    binaryDisassemble.h
    binaryfilecli.h
    rawcli.h
    rawDisassemble.h
)

add_executable(${PROJECT_NAME} ${SourceFiles} ${HeaderFiles})

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})
