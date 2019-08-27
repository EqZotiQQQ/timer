cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCES
    main.cpp
    timer.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(untitled ${SOURCES})

target_link_libraries(untitled Threads::Threads)
