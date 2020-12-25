project(${CMAKE_PROJECT_NAME}_TEST)
cmake_minimum_required(VERSION 3.10)

download_file(https://github.com/catchorg/Catch2/releases/download/v2.13.0/catch.hpp 
              ${CMAKE_SOURCE_DIR}/packages/catch2/catch.hpp
              MD5
              209cbb2f8f37224cc5f7261cf9388bc2)

include_directories(${CMAKE_SOURCE_DIR}/packages/ ${CMAKE_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} test.cpp)
#if(MSVC)
#    set(CMAKE_PROJECT_NAME_LIB "${CMAKE_STATIC_LIBRARY_PREFIX}CMAKE_PROJECT_NAME${CMAKE_STATIC_LIBRARY_SUFFIX}")
#    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME_LIB})
#else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME})
#endif()
