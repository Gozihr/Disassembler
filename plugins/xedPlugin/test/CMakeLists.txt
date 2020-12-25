project(XED_TEST)
cmake_minimum_required(VERSION 3.10)

download_file(https://github.com/catchorg/Catch2/releases/download/v2.13.0/catch.hpp 
              ${CMAKE_SOURCE_DIR}/packages/catch2/catch.hpp
              MD5
              209cbb2f8f37224cc5f7261cf9388bc2)

set(XED ${CMAKE_SOURCE_DIR}/packages/xed)
include_directories(${XED}/include ${CMAKE_SOURCE_DIR}/packages/ ${CMAKE_SOURCE_DIR}/plugins/xedPlugin)
add_executable(${PROJECT_NAME} test.cpp)

if(MSVC)
    # Note this is an inelegant hack to get tests building on windows
    target_link_libraries(${PROJECT_NAME} PRIVATE libxedPlugin)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE xedPlugin)
endif()