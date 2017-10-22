cmake_minimum_required(VERSION 3.8)
project(same_glasses)

set(CMAKE_CXX_STANDARD 11)

if(MINGW)
    set(BUILD_SHARED_LIBS OFF)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static-libgcc -static-libstdc++")
endif()

set(SOURCE_FILES
        main.cpp
        include/cl_error.h cl_error.cpp
        include/data.h data.cpp
        include/gui.h gui.cpp)
add_executable(same_glasses ${SOURCE_FILES})

set(Qt5Network_DIR c:/Qt/5.9.2/mingw53_32/lib/cmake/Qt5Network)
set(Qt5Network_DIR c:/Qt/5.9.2/mingw53_32/lib/cmake/Qt5Gui)
set(Qt5Network_DIR c:/Qt/5.9.2/mingw53_32/lib/cmake/Qt5UiTools)
find_package(Qt5Network REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5UiTools REQUIRED)

#include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
include_directories("c:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v8.0\\include")

target_link_libraries(same_glasses
        "c:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v8.0/lib/Win32/OpenCL.lib"
        Qt5::Gui
        Qt5::UiTools
        Qt5::Network)

configure_file(program.cl program.cl COPYONLY)
configure_file(data_sun.csv data_sun.csv COPYONLY)