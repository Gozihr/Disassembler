project(xedPlugin)
cmake_minimum_required(VERSION 3.10)
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

function(download_xed)
execute_process (
    # This creates an unfortunate bash dependency for windows.
    # And adds a wget dependency to mac and linux.
    # Works for my crossplat process but could be troublesome for others.
    COMMAND bash -c "${CMAKE_SOURCE_DIR}/scripts/setupXED.sh"
)
endfunction(download_xed)

function(build_xed)
execute_process (
    #Linux builds with download_xed but doesn't run
    #seems like lack of abi stability
    COMMAND bash -c "${CMAKE_SOURCE_DIR}/scripts/buildXED.sh"
)
endfunction(build_xed)

if(LINUX) 
    build_xed()
else()
    download_xed()
endif()

set(XED ${CMAKE_SOURCE_DIR}/packages/xed)
include_directories(${CMAKE_SOURCE_DIR}/src/interfaces ${XED}/include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14")

set(SOURCE_FILES xedDisassembler.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

link_directories(${XED}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE -L${XED}/lib -lxed)

add_subdirectory (test)