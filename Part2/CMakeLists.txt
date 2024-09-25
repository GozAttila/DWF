cmake_minimum_required(VERSION 3.10)
project(DWFPart2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# If needed
# set(OPENSSL_ROOT_DIR "")
# set(ZLIB_INCLUDE_DIR "")
# set(ZLIB_LIBRARY "")

find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
find_package(ZLIB REQUIRED)

add_executable(DWFPart2 main.cpp utils.cpp trade.cpp)

# See above comment
target_include_directories(DWFPart2 PRIVATE ${ZLIB_INCLUDE_DIR})
target_link_libraries(DWFPart2 CURL::libcurl OpenSSL::SSL OpenSSL::Crypto ${ZLIB_LIBRARY})