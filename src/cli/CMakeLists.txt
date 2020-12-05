project(disasm)
cmake_minimum_required(VERSION 3.10)

download_file(https://raw.githubusercontent.com/farzonl/CmdParser/feature/customization/cmdparser.hpp
              ../packages/cmdParser/cmdparser.hpp
              MD5
              f9206b10f4555bb775aadfb058905f85)


include_directories(${CMAKE_SOURCE_DIR}/packages/ ${CMAKE_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} main.cpp autocli.cpp rawcli.cpp rawDisassemble.cpp binaryfilecli.cpp binaryDisassemble.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})
