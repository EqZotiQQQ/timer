cmake_minimum_required(VERSION 3.10)

project(timer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(HEADERS
    headers/timer.h
    headers/timeruser.h
)

set(SOURCES
    main.cpp
    src/timer.cpp
    src/timeruser.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_executable(timer ${SOURCES} ${HEADERS})

target_link_libraries(timer Threads::Threads)
