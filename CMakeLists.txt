project(Disassembler)
cmake_minimum_required(VERSION 3.23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

function(download_file url filename hash_type hash)

if(NOT EXISTS ${filename})
  file(DOWNLOAD ${url} ${filename}
       TIMEOUT 60  # seconds
       EXPECTED_HASH ${hash_type}=${hash}
       TLS_VERIFY ON
      )
endif()

endfunction(download_file)

function(decompress tarfile path)
if(NOT EXISTS ${path})
    get_filename_component(FILE_EXT ${tarfile} LAST_EXT)
    get_filename_component(PATH_PARENT ${path} DIRECTORY)
    if(WIN32)
        execute_process (
            COMMAND powershell.exe -ExecutionPolicy Bypass Expand-Archive -LiteralPath ${tarfile} -DestinationPath ${PATH_PARENT}
        )
        execute_process (
            COMMAND powershell.exe -ExecutionPolicy Bypass -Command "${CMAKE_SOURCE_DIR}/scripts/renameDir.ps1 ${path} ${tarfile}"
        )
    elseif(LINUX AND ${FILE_EXT} STREQUAL ".zip")
        execute_process (
            COMMAND unzip -qq ${tarfile} -d ${PATH_PARENT}
        )
        execute_process (
            COMMAND bash -c "${CMAKE_SOURCE_DIR}/scripts/renameDir.sh ${path} ${tarfile}"
        )
    else()
        execute_process ( COMMAND mkdir -p ${path})
        execute_process (COMMAND tar -xzvf ${tarfile} -C ${path} --strip-components 1)
    endif()
endif()
endfunction(decompress)


function(buildLIEF srcPath buildPath installPath buildType)
    if(WIN32)
        string(TOUPPER ${buildType} buildTypeUpper)
        set(LIEFCRTTYPE -DLIEF_USE_CRT_${buildTypeUpper}=${MTPOSTFIX})
    endif()
    
    execute_process (
        COMMAND cmake -S ${srcPath} -B ${buildPath} -DCMAKE_BUILD_TYPE=${buildType} ${LIEFCRTTYPE} 
    )
    execute_process (
        #COMMAND msbuild ${buildPath}\LIEF.sln -t:Build -p:Configuration=${buildType}
        COMMAND cmake --build ${buildPath} --target LIB_LIEF --config ${buildType}
    )
    execute_process (
        COMMAND cmake --install ${buildPath} --prefix ${installPath} --config ${buildType}
    )
endfunction(buildLIEF)

if(WIN32)
    if(CMAKE_BUILD_TYPE MATCHES Release)
        set(MTPOSTFIX MT)
    elseif(CMAKE_BUILD_TYPE MATCHES Debug)
        set(MTPOSTFIX MTd)
    endif()
endif()

set(LIEF_VERSION "0.12.1")
if( DEFINED BUILDLIEFSRC OR (WIN32 AND CMAKE_BUILD_TYPE MATCHES Debug))
    message(STATUS  "starting a LIEF source build")
    download_file(https://github.com/lief-project/LIEF/archive/${LIEF_VERSION}.zip
                  ${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}.zip
                  MD5
                  465563d8342e148a3d82b6b1cb36bd11
    )
    decompress(${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}.zip ${CMAKE_SOURCE_DIR}/packages/LIEF-src)
    buildLIEF(${CMAKE_SOURCE_DIR}/packages/LIEF-src
              ${CMAKE_SOURCE_DIR}/packages/LIEF-build
              ${CMAKE_SOURCE_DIR}/packages/LIEF
              ${CMAKE_BUILD_TYPE}
    )
    #if it isn't set, set it to true
    set(BUILDLIEFSRC true)
else()
    if(LINUX)
        download_file(https://github.com/lief-project/LIEF/releases/download/${LIEF_VERSION}/LIEF-${LIEF_VERSION}-Linux-x86_64.tar.gz
                  ${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}.tar.gz
                  MD5
                  eb604e6d494e86a888e41ef4df549b3a)
        decompress(${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}.tar.gz ${CMAKE_SOURCE_DIR}/packages/LIEF)
    elseif(WIN32)
        download_file(https://github.com/lief-project/LIEF/releases/download/${LIEF_VERSION}/LIEF-${LIEF_VERSION}-win64.zip
                      ${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}-win64.zip
                      MD5
                      ca4665c47fb6d4b68a30199195fa7037)
        decompress(${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}-win64.zip ${CMAKE_SOURCE_DIR}/packages/LIEF)
    elseif(APPLE)
        download_file(https://github.com/lief-project/LIEF/releases/download/${LIEF_VERSION}/LIEF-${LIEF_VERSION}-Darwin-x86_64.tar.gz
                      ${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}.tar.gz
                      MD5
                      5d609361f22b6f9a8dc22f2c6fb541a7)
        decompress(${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}.tar.gz ${CMAKE_SOURCE_DIR}/packages/LIEF)
    else()
    message(FATAL_ERROR  "No other platforms are supported.")
    endif()
endif()


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
    # Default debug flags are OK 
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
endif()

add_subdirectory (src)
if(BUILD_INT_TESTS)
    add_subdirectory(int-tests)
endif()
add_subdirectory (plugins)

