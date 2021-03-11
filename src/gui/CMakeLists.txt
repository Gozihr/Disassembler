project(disasm-gui)

#Look up OpenGL
find_package(OpenGL REQUIRED)
find_package(GLM) # Look up GLM
find_package(glfw3 3.3) # Look up glfw

download_file(https://gist.github.com/farzonl/f724000a4fd841c792c82a36c0da8cba/raw/b6125287d4364e0982c970045691bf6d319c9868/glad.zip
              ${CMAKE_SOURCE_DIR}/packages/glad.zip 
              MD5
              262e8984dbde2f359207ffa8e609aa50)

decompress(${CMAKE_SOURCE_DIR}/packages/glad.zip ${CMAKE_SOURCE_DIR}/packages/glad)

#Link GLAD
add_subdirectory(${CMAKE_SOURCE_DIR}/packages/glad/ ${CMAKE_CURRENT_BINARY_DIR}/glad)
include_directories(${CMAKE_SOURCE_DIR}/packages/glad/include)

if(${glfw3_FOUND})
   MESSAGE(STATUS "Found GLFW3.")
else()
    MESSAGE(STATUS "Could not locate GLFW3, downloading.")
    download_file(https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.zip
                 ${CMAKE_SOURCE_DIR}/packages/glfw-3.3.2.zip
                 MD5
                 f794d9ad899a64894782884be79d644b)
    decompress(${CMAKE_SOURCE_DIR}/packages/glfw-3.3.2.zip ${CMAKE_SOURCE_DIR}/packages/glfw)
    add_subdirectory(${CMAKE_SOURCE_DIR}/packages/glfw/ ${CMAKE_CURRENT_BINARY_DIR}/glfw)
    include_directories(${CMAKE_SOURCE_DIR}/packages/glfw/include)
endif()

if(${GLM_FOUND})
    MESSAGE(STATUS "Found GLM.")
else()
    MESSAGE(STATUS "Could not locate GLM, downloading.")
    download_file(https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
              ${CMAKE_SOURCE_DIR}/packages/glm-0.9.9.8.zip
              MD5
              69895110052f0d711c9c54fbf385f6f5)
    decompress(${CMAKE_SOURCE_DIR}/packages/glm-0.9.9.8.zip ${CMAKE_SOURCE_DIR}/packages/glm)
    include_directories(${CMAKE_SOURCE_DIR}/packages/glm)
endif()

# imgui
download_file("https://github.com/ocornut/imgui/archive/v1.81.zip"
                 ${CMAKE_SOURCE_DIR}/packages/imgui-1.81.zip
                 MD5
                 78af0cf170fb3f2a431eb39cac7f55b8)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/packages/imgui)
decompress(${CMAKE_SOURCE_DIR}/packages/imgui-1.81.zip ${IMGUI_DIR})
include_directories(${IMGUI_DIR})



if(APPLE)
  message(STATUS "APPLE Platform detected")
  include_directories(/System/Library/Frameworks)
  include_directories(/usr/local/include)
  find_library(COCOA_LIBRARY Cocoa REQUIRED)
  find_library(OpenGL_LIBRARY OpenGL)
  find_library(IOKIT_LIBRARY IOKit REQUIRED)
  find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
  set(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif()

if(LINUX)
  set(EXTRA_LIBS ${CMAKE_DL_LIBS})
endif()

set(ImguiSource
    ${IMGUI_DIR}/imgui.cpp 
    ${IMGUI_DIR}/imgui_demo.cpp 
    ${IMGUI_DIR}/imgui_draw.cpp 
    ${IMGUI_DIR}/imgui_tables.cpp 
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp 
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set (SourceFiles
    main.cpp
)

set(HeaderFiles
)

include_directories(${CMAKE_SOURCE_DIR}/packages/ ${DISASSEMBLER_SOURCE_DIR})

set(GL_LIBS OpenGL::GL glfw glad ${EXTRA_LIBS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_IMPL_OPENGL_LOADER_GLAD")

add_executable(${PROJECT_NAME} ${SourceFiles} ${HeaderFiles} ${ImguiSource})

target_link_libraries(${PROJECT_NAME} PRIVATE ${GL_LIBS})

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)