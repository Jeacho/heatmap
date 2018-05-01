cmake_minimum_required(VERSION 2.6)
project(plot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_C_FLAGS_DEBUG "-O0")
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

file(GLOB SOURCES
    "implement/*.cpp"
"implement/Heatmap/*.cpp"
"implement/Color/*.cpp")

add_executable(plot ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(plot ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
