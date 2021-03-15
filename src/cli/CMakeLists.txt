project(disasm)
cmake_minimum_required(VERSION 3.10)

download_file(https://raw.githubusercontent.com/FlorianRappl/CmdParser/3b5e2f284e0e29543eaf51ac53a01dd3b6d468ce/cmdparser.hpp
              ${CMAKE_SOURCE_DIR}/packages/cmdParser/cmdparser.hpp
              MD5
              8449f7da1097659698193bc0ddb24ef7)

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
     configcli.cpp
     defaultcli.cpp
     rawcli.cpp
     replcli.cpp
)

set(HeaderFiles
    autocli.h
    basecli.h
    binaryfilecli.h
    configcli.h
    defaultcli.h
    rawcli.h
    replcli.h
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
endif()

add_executable(${PROJECT_NAME} ${SourceFiles} ${HeaderFiles})

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})
