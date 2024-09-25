cmake_minimum_required(VERSION 3.10)
project(DWFPart1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(CURL REQUIRED)

add_executable(DWFPart1 main.cpp hash_table.cpp murmur_hash.cpp utils.cpp)

target_link_libraries(DWFPart1 CURL::libcurl)