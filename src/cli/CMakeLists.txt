project(disasm)
cmake_minimum_required(VERSION 3.10)

download_file(https://raw.githubusercontent.com/FlorianRappl/CmdParser/master/cmdparser.hpp
              ../packages/cmdParser/cmdparser.hpp
              MD5
              7680d10af49010f8b349906bd2a5ac5b)


include_directories(${CMAKE_SOURCE_DIR}/packages/ ${CMAKE_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})
