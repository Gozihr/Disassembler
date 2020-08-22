project(${CMAKE_PROJECT_NAME}_TEST)
cmake_minimum_required(VERSION 3.10)

download_file(https://github.com/catchorg/Catch2/releases/download/v2.13.0/catch.hpp 
              ../packages/catch2/catch.hpp
              MD5
              209cbb2f8f37224cc5f7261cf9388bc2)

include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})
