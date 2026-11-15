cmake_minimum_required(VERSION 3.15)

project(LearnOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default install prefix to the project root, so "install" lands in ./bin
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR} CACHE PATH "" FORCE)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

find_package(OpenGL REQUIRED)

add_executable(LearnOpenGL 
    src/main.cpp
    src/glad.c
)

target_include_directories(LearnOpenGL PRIVATE 
    include
    external
)

target_link_libraries(LearnOpenGL PRIVATE 
    OpenGL::GL
    glfw
    ${CMAKE_DL_LIBS}
)

install(TARGETS LearnOpenGL RUNTIME DESTINATION bin)