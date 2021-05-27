cmake_minimum_required(VERSION 3.10)

project(fast_Request)

set(
    CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -g"
)



add_library(
    objects OBJECT
    Connect.cpp
    Connect.h
    Url.h
)

add_executable(
    main
    main.cpp
)

set_property( TARGET main PROPERTY CXX_STANDARD 17 )
set_property( TARGET objects PROPERTY CXX_STANDARD 17 )

target_link_libraries(
    main
    PUBLIC objects
    PUBLIC -ldl
)