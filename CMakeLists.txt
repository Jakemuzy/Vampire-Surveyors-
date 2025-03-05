cmake_minimum_required(VERSION 3.18)

PROJECT(Vampire-Survivors)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/include/SDL3/cmake)

find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

file( GLOB SOURCES "src/*.cpp" "src/*.c")
link_directories(${PROJECT_SOURCE_DIR}/libs)

add_executable( Vampire-Survivors ${SOURCES} )  # MAKE SURE TO ADD THE DLL TO THE EXECUTABLE FOLDER IN ORDER TO RUN

target_include_directories(
    Vampire-Survivors
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/libs
)
target_link_libraries(
    Vampire-Survivors
    PRIVATE 
        SDL3
)


if(WIN32)
    set_target_properties(Vampire-Survivors PROPERTIES
                          RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()