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
if(WIN32)
    execute_process (
        COMMAND powershell.exe -ExecutionPolicy Bypass -File "${CMAKE_SOURCE_DIR}/scripts/buildXED.ps1"
    )
else()
    #Linux builds with download_xed but doesn't run
    #seems like lack of abi stability
    execute_process (
        COMMAND bash -c "${CMAKE_SOURCE_DIR}/scripts/buildXED.sh"
)
endif()
endfunction(build_xed)

if(LINUX OR WIN32) 
    build_xed()
else()
    download_xed()
endif()

set(XED ${CMAKE_SOURCE_DIR}/packages/xed)
include_directories(${CMAKE_SOURCE_DIR}/src/interfaces ${XED}/include)

set (SourceFiles
     xedDisassembler.cpp
     xedLibInterface.cpp
)

set(HeaderFiles
    xedDisassembler.h

)

if(WIN32)
    list(APPEND SourceFiles
         ../dllmain.cpp
    )
endif()

set(XED_LIB_FULL_PATH "${XED}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}xed${CMAKE_STATIC_LIBRARY_SUFFIX}")
add_library(xedLib STATIC IMPORTED)
SET_TARGET_PROPERTIES(xedLib PROPERTIES IMPORTED_LOCATION ${XED_LIB_FULL_PATH})

add_library(${PROJECT_NAME} SHARED ${SourceFiles} ${HeaderFiles})
set(XED_LDFLAGS -L${XED}/lib -lxed)
if(MSVC)
    add_library(lib${PROJECT_NAME} STATIC ${SourceFiles} ${HeaderFiles})
    target_link_libraries(lib${PROJECT_NAME} PUBLIC  xedLib)
    set(XED_LDFLAGS ${XED_LIB_FULL_PATH})
endif()

link_directories(${XED}/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC  xedLib)

add_subdirectory (test)