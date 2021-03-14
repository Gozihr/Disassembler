project(Disassembler)
cmake_minimum_required(VERSION 3.16)
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

set(LIEF_VERSION "0.11.3")
if( DEFINED BUILDLIEFSRC OR (WIN32 AND CMAKE_BUILD_TYPE MATCHES Debug))
    message(STATUS  "starting a LIEF source build")
    download_file(https://github.com/lief-project/LIEF/archive/${LIEF_VERSION}.zip
                  ${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}.zip
                  MD5
                  fc6f9e277de0f25993007c0b10de2daf
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
                  cffdd77556bd35e8cc32ff9742605a4e)
        decompress(${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}.tar.gz ${CMAKE_SOURCE_DIR}/packages/LIEF)
    elseif(WIN32)
        download_file(https://github.com/lief-project/LIEF/releases/download/${LIEF_VERSION}/LIEF-${LIEF_VERSION}-win64.zip
                      ${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}-win64.zip
                      MD5
                      a5e6a5ef5933b1296739d859b198f857)
        decompress(${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}-win64.zip ${CMAKE_SOURCE_DIR}/packages/LIEF)
    elseif(APPLE)
        download_file(https://github.com/lief-project/LIEF/releases/download/${LIEF_VERSION}/LIEF-${LIEF_VERSION}-Darwin-x86_64.tar.gz
                      ${CMAKE_SOURCE_DIR}/packages/LIEF-${LIEF_VERSION}.tar.gz
                      MD5
                      d033f69581f61386cca64ff0fb9b4e88)
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

