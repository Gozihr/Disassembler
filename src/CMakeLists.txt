project(${CMAKE_PROJECT_NAME})
cmake_minimum_required(VERSION 3.10)

set(LIEF ${CMAKE_SOURCE_DIR}/packages/LIEF)
set(LIEF_LDFLAGS -L${LIEF}/lib -lLIEF)
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
        set(CAPSTONE_LDFLAGS ${CAPSTONE_DIR}/capstone.lib)
        include_directories(${CAPSTONE_INCLUDE_DIRS}
                    ${LIEF}/include)
        
        set(LIEF_LDFLAGS ${LIEF}/lib/LIEF.lib)
endif()

include_directories(${CAPSTONE_INCLUDE_DIRS}/..
                    ${LIEF}/include)

if(MSVC)
    # since this builds a shared lib set the right flags
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

set(SOURCE_FILES disassemble.cpp capstoneDisassembler.cpp parser.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CAPSTONE_LDFLAGS}  ${LIEF_LDFLAGS})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER disassemble.h)

INSTALL(TARGETS ${PROJECT_NAME} 
        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/bin/
        PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/include/
)

add_subdirectory (cli)
add_subdirectory (test)


