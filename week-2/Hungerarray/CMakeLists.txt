cmake_minimum_required(VERSION 3.10)

project(fast_Request)

set(
    CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall"
)

add_library(
    objects OBJECT
    Connect.cpp Connect.h
    Url.h
    WebRequestAbstract.h
    HttpRequest.cpp HttpRequest.h
    HttpsRequest.cpp HttpsRequest.h
)

target_compile_definitions(objects PUBLIC LOG)

add_executable(
    child
    child.cpp
)

add_executable(
    main
    main.cpp
)

set_property( TARGET main PROPERTY CXX_STANDARD 17 )
set_property( TARGET child PROPERTY CXX_STANDARD 17)
set_property( TARGET objects PROPERTY CXX_STANDARD 17 )

target_link_libraries(
    child
    PUBLIC objects
    PUBLIC -ldl
    PUBLIC -lssl
    PUBLIC -lcrypto
)