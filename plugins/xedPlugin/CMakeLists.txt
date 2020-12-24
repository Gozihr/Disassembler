project(xedPlugin)
cmake_minimum_required(VERSION 3.10)

function(download_xed)
if(WIN32 AND MSVC)
    execute_process (
        COMMAND powershell.exe -ExecutionPolicy Bypass -File "${CMAKE_SOURCE_DIR}/scripts/setupXED.ps1"
    )
else()
    execute_process (
        # If you are using MinGW or Cygwin we will use bash
        # This creates a crossplat bash and wget dependency.
        COMMAND bash -c "${CMAKE_SOURCE_DIR}/scripts/setupXED.sh"
    )
endif()
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

set(SOURCE_FILES xedDisassembler.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

set(XED_LDFLAGS -L${XED}/lib -lxed)

if(MSVC)
    set(XED_LDFLAGS ${XED}/lib/xed.lib)
endif()

link_directories(${XED}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE  ${XED_LDFLAGS})

add_subdirectory (test)