project(disasm)
cmake_minimum_required(VERSION 3.10)

download_file(https://raw.githubusercontent.com/FlorianRappl/CmdParser/b5288792d91fa6e962217f2ab37c60445dade105/cmdparser.hpp
              ${CMAKE_SOURCE_DIR}/packages/cmdParser/cmdparser.hpp
              MD5
              2f3c0d82333d6668774ffa98c1c8e3f2)

download_file(https://github.com/nlohmann/json/releases/download/v3.9.1/json.hpp
              ${CMAKE_SOURCE_DIR}/packages/nlohmann/json.hpp
              SHA256
              7804b38146921d03374549c9e2a5e3acda097814c43caf2b96a0278e58df26e0
)

include_directories(${CMAKE_SOURCE_DIR}/packages/ ${CMAKE_SOURCE_DIR}/src)

set (SourceFiles
     main.cpp
     autocli.cpp
     binaryfilecli.cpp
     binaryDisassemble.cpp
     configcli.cpp
     defaultcli.cpp
     rawcli.cpp
     rawDisassemble.cpp
     replcli.cpp
)

set(HeaderFiles
    autocli.h
    basecli.h
    binaryDisassemble.h
    binaryfilecli.h
    configcli.h
    defaultcli.h
    rawcli.h
    rawDisassemble.h
    replcli.h
)

add_executable(${PROJECT_NAME} ${SourceFiles} ${HeaderFiles})

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})
