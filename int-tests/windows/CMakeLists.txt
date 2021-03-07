if(UNIX)
    add_subdirectory(mingw)
endif(UNIX)

if(WIN32)
    add_subdirectory(link)
endif(WIN32)
