project(${CMAKE_PROJECT_NAME})
cmake_minimum_required(VERSION 3.10)

#find dependencies
include(FindPkgConfig)
pkg_check_modules (CAPSTONE REQUIRED capstone)

include_directories(${CMAKE_SOURCE_DIR}/packages/ ${CAPSTONE_INCLUDE_DIRS}/..)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14" )

set(SOURCE_FILES disassemble.cpp capstoneDisassembler.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CAPSTONE_LDFLAGS} )
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER disassemble.h)

INSTALL(TARGETS ${PROJECT_NAME} 
        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/bin/
        PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/include/
)

add_subdirectory (cli)
add_subdirectory (test)


