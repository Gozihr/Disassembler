project(${CMAKE_PROJECT_NAME})
cmake_minimum_required(VERSION 3.10)

set(LIEF_DIR ${CMAKE_SOURCE_DIR}/packages/LIEF)
set(LIEF_INCLUDE_DIR ${LIEF_DIR}/include)
#set(LIEF_LDFLAGS -L${LIEF_DIR}/lib -lLIEF)
set(DISASSEMBLER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TargetLibraries "")
#find dependencies
if(UNIX)
        include(FindPkgConfig)
        pkg_check_modules (CAPSTONE REQUIRED capstone)
        set(LIEF__LIB_FULL_PATH "${LIEF_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}LIEF${CMAKE_STATIC_LIBRARY_SUFFIX}")
        add_library(LibLIEF STATIC IMPORTED)
        SET_TARGET_PROPERTIES(LibLIEF PROPERTIES IMPORTED_LOCATION ${LIEF__LIB_FULL_PATH})
        list(APPEND TargetLibraries
             LibLIEF
        )   
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
        set(LIEF_LDFLAGS "${LIEF_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}LIEF${MTPOSTFIX}${CMAKE_STATIC_LIBRARY_SUFFIX}")
        list(APPEND TargetLibraries
             ${LIEF_LDFLAGS}
        )
endif()

set(IncludeDirs ${CAPSTONE_INCLUDE_DIRS}/..
                ${LIEF_INCLUDE_DIR}
)
list(APPEND TargetLibraries
             ${CAPSTONE_LDFLAGS}
)

if(LINUX)
    pkg_check_modules (GLIB2 REQUIRED glib-2.0)
    pkg_check_modules (GLIB2_MODULE REQUIRED gmodule-2.0)
    list(APPEND IncludeDirs
        ${GLIB2_INCLUDE_DIRS}
        ${GLIB2_MODULE}
    )
    list(APPEND TargetLibraries
         ${GLIB2_LIBRARIES}
         ${GLIB2_MODULE_LIBRARIES}
         ${LIBEDIT_LIBRARIES}
    )
endif()

if(UNIX)
    find_package(Curses REQUIRED)
    list(APPEND TargetLibraries 
        ${CURSES_LIBRARIES}
        "-ledit"
    )
endif()

include_directories(${IncludeDirs})


set(SourceFiles disassemble.cpp 
                capstoneDisassembler.cpp 
                disassemble.cpp
                dynamicDisassembler.cpp
                parser.cpp
)

set(HeaderFiles
    capstoneDisassembler.h
    disassemble.h
    dynamicDisassembler.h
    parser.h
    interfaces/helpers.h
    interfaces/instruction.h
    interfaces/types.h
    interfaces/interfaceDisassembler.h
    interfaces/pch.h
)

add_library(${PROJECT_NAME} STATIC ${SourceFiles} ${HeaderFiles}
            $<TARGET_OBJECTS:Disassembler.Plugin>
            $<TARGET_OBJECTS:Disassembler.DataPattern>
            $<TARGET_OBJECTS:Disassembler.Diff>
            $<TARGET_OBJECTS:Disassembler.Repl>
            $<TARGET_OBJECTS:Disassembler.Runtime>
            $<TARGET_OBJECTS:Disassembler.Version>
)

target_link_libraries(${PROJECT_NAME} ${TargetLibraries})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER disassemble.h)

if(MSVC)
    # Used for the 'and', 'or' ... keywords - See: http://www.cplusplus.com/reference/ciso646/
    target_compile_options(${PROJECT_NAME} PUBLIC /FIiso646.h)
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
add_subdirectory(dataPattern)
add_subdirectory (gui)
add_subdirectory (diff)
add_subdirectory (runtime)
add_subdirectory(pluginInfra)
add_subdirectory(repl)
add_subdirectory (test)
add_subdirectory (version)



