project(Disassembler)
cmake_minimum_required(VERSION 3.10)
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
    if(WIN32)
        execute_process (
            COMMAND cmd.exe /c mkdir ${path}
            #COMMAND 7z x ${tarfile}  -o${path} #Note Expand-Archive can be slow can replace with 7z
            COMMAND powershell.exe -ExecutionPolicy Bypass Expand-Archive -LiteralPath ${tarfile} -DestinationPath ${path}
        )
        execute_process (
            COMMAND powershell.exe -ExecutionPolicy Bypass -Command "${CMAKE_SOURCE_DIR}/scripts/moveFiles.ps1 ${path} ${tarfile}"
        )
    else()
        execute_process (
            COMMAND mkdir ${path}
            COMMAND tar -xzvf ${tarfile} -C ${path} --strip-components 1    
        )
    endif()
endif()

endfunction(decompress)


if(LINUX)
    download_file(https://github.com/lief-project/LIEF/releases/download/0.10.1/LIEF-0.10.1-Linux.tar.gz
              ${CMAKE_SOURCE_DIR}/packages/LIEF-0.10.1.tar.gz
              MD5
              15f14210a342616def57e8344b9a5d5c)
    decompress(${CMAKE_SOURCE_DIR}/packages/LIEF-0.10.1.tar.gz ${CMAKE_SOURCE_DIR}/packages/LIEF)
elseif(WIN32)
    download_file(https://github.com/lief-project/LIEF/releases/download/0.10.1/LIEF-0.10.1-win64.zip
              ${CMAKE_SOURCE_DIR}/packages/LIEF-0.10.1.zip
              MD5
              a3bcf27708f46278519c5443857627c4)
    decompress(${CMAKE_SOURCE_DIR}/packages/LIEF-0.10.1.zip ${CMAKE_SOURCE_DIR}/packages/LIEF)
elseif(APPLE)
    download_file(https://github.com/lief-project/LIEF/releases/download/0.10.1/LIEF-0.10.1-Darwin.tar.gz
              ${CMAKE_SOURCE_DIR}/packages/LIEF-0.10.1.tar.gz
              MD5
              88ce790a24fd4683950b3aa1536128ae)
    decompress(${CMAKE_SOURCE_DIR}/packages/LIEF-0.10.1.tar.gz ${CMAKE_SOURCE_DIR}/packages/LIEF)
else()
message(FATAL_ERROR  "No other platforms are supported.")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
    # Default debug flags are OK 
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14" )
endif()

add_subdirectory (src)
add_subdirectory (plugins)

