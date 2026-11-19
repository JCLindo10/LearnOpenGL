cmake_minimum_required(VERSION 3.15)

project(LearnOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
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
    src/window.cpp
    src/shader.cpp
    src/main.cpp
    src/glad.c
    src/vertex.cpp
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

add_executable(hello_triangle_exercises
    src/window.cpp
    src/shader.cpp
    src/vertex.cpp
    src/hello_triangle_exercises.cpp
    src/glad.c
)

target_include_directories(hello_triangle_exercises PRIVATE
    include
    external
)

target_link_libraries(hello_triangle_exercises PRIVATE
    OpenGL::GL
    glfw
    ${CMAKE_DL_LIBS}
)

add_executable(chapter6
    src/window.cpp
    src/shader.cpp
    src/vertex.cpp
    src/glad.c
    src/chapter6.cpp
)

target_include_directories(chapter6 PRIVATE
    include
    external
)

target_link_libraries(chapter6 PRIVATE
    OpenGL::GL
    glfw
    ${CMAKE_DL_LIBS}
)

install(TARGETS LearnOpenGL hello_triangle_exercises chapter6 RUNTIME DESTINATION bin)