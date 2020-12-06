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
execute_process (
    COMMAND mkdir ${path}
    COMMAND tar -xzvf ${tarfile} -C ${path} --strip-components 1
)
endfunction(decompress)


if(LINUX)
download_file(https://github.com/lief-project/LIEF/releases/download/0.10.1/LIEF-0.10.1-Linux.tar.gz
              ../packages/LIEF-0.10.1.tar.gz
              MD5
              15f14210a342616def57e8344b9a5d5c)
decompress(../packages/LIEF-0.10.1.tar.gz ../packages/LIEF)
elseif(WIN32)
download_file(https://github.com/lief-project/LIEF/releases/download/0.10.1/LIEF-0.10.1-win64.zip
              ../packages/LIEF-0.10.1.zip
              MD5
              a3bcf27708f46278519c5443857627c4)
elseif(APPLE)
download_file(https://github.com/lief-project/LIEF/releases/download/0.10.1/LIEF-0.10.1-Darwin.tar.gz
              ../packages/LIEF-0.10.1.tar.gz
              MD5
              88ce790a24fd4683950b3aa1536128ae)
decompress(../packages/LIEF-0.10.1.tar.gz ../packages/LIEF)
else()
message("No other platforms are supported.")
endif()

add_subdirectory (src)
add_subdirectory (plugins)

