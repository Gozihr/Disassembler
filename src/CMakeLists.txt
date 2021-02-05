project(${CMAKE_PROJECT_NAME})
cmake_minimum_required(VERSION 3.10)

set(LIEF_DIR ${CMAKE_SOURCE_DIR}/packages/LIEF)
set(LIEF_LDFLAGS -L${LIEF_DIR}/lib -lLIEF)
set(DISASSEMBLER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
#find dependencies
if(UNIX)
        include(FindPkgConfig)
        pkg_check_modules (CAPSTONE REQUIRED capstone)
elseif(WIN32)
        download_file(https://github.com/aquynh/capstone/releases/download/4.0.2/capstone-4.0.2-win64.zip
              ${CMAKE_SOURCE_DIR}/packages/capstone-4.0.2-win64.zip
              MD5
              a6ad5a3bd6842cb7fadc3f3e5ed8bf20)
        decompress(${CMAKE_SOURCE_DIR}/packages/capstone-4.0.2-win64.zip ${CMAKE_SOURCE_DIR}/packages/capstone)
        set(CAPSTONE_DIR ${CMAKE_SOURCE_DIR}/packages/capstone)
        # find-pkg gives the path include/capstone. To stay consistent I will do the same.
        set(CAPSTONE_INCLUDE_DIRS ${CAPSTONE_DIR}/include/capstone)

        set(CAPSTONE_LDFLAGS "${CAPSTONE_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}capstone${CMAKE_STATIC_LIBRARY_SUFFIX}")
        set(LIEF_LDFLAGS "${LIEF_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}LIEF${CMAKE_STATIC_LIBRARY_SUFFIX}")
endif()

include_directories(${CAPSTONE_INCLUDE_DIRS}/..
                    ${LIEF_DIR}/include)


set(SourceFiles disassemble.cpp 
                capstoneDisassembler.cpp 
                parser.cpp
)

set(HeaderFiles
    capstoneDisassembler.h
    disassemble.h
    parser.h
)

add_library(${PROJECT_NAME} STATIC ${SourceFiles} ${HeaderFiles}
            $<TARGET_OBJECTS:Disassembler.Plugin>
            $<TARGET_OBJECTS:Disassembler.DataPattern>
)

target_link_libraries(${PROJECT_NAME} ${CAPSTONE_LDFLAGS}  ${LIEF_LDFLAGS})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER disassemble.h)

if(MSVC)
    # Used for the 'and', 'or' ... keywords - See: http://www.cplusplus.com/reference/ciso646/
    target_compile_options(${PROJECT_NAME} PUBLIC /FIiso646.h)
    
    #TODO experiment with the below as a replacement for /MT to fix cmake warnings
    #set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_FLAGS /NODEFAULTLIB:MSVCRT)
    #set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_FLAGS /NODEFAULTLIB:LIBCMT)
endif()

INSTALL(TARGETS ${PROJECT_NAME} 
        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/bin/
        PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/include/
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  # Add include_directories here
  plugininfra
)

add_subdirectory (cli)
add_subdirectory (test)
add_subdirectory(pluginInfra)
add_subdirectory(dataPattern)


