cmake_minimum_required(VERSION 3.10)

project(fast_Request)

set(
    CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -g"
)

add_executable(
    main
    main.cpp
)

target_include_directories(
    main
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/asio/include/
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/openssl/include/
)

target_link_libraries(
    main
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/openssl/lib/libssl.a
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/openssl/lib/libcrypto.a
    PUBLIC -ldl
)