cmake_minimum_required(VERSION 3.11)

project(cppnbstripout LANGUAGES CXX)

include(FetchContent)

message(STATUS "Installing nlohmann_json")
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/archive/v3.7.3.tar.gz
    URL_MD5 846bbc611ce9ecd7d45d6554679245e1
)
FetchContent_MakeAvailable(nlohmann_json)

message(STATUS "Installing argparse")
FetchContent_Declare(
    argparse
    URL https://github.com/p-ranav/argparse/archive/v2.0.tar.gz
    URL_MD5 3fe36006956b05fe39f3c85f9ed41af0
)
FetchContent_MakeAvailable(argparse)

add_executable(cppnbstripout cppnbstripout.cpp)
target_compile_features(cppnbstripout PUBLIC cxx_std_17)
target_link_libraries(cppnbstripout PRIVATE nlohmann_json::nlohmann_json argparse::argparse)

# statically linked executables do not work on macOS
if(NOT APPLE)
  target_link_libraries(cppnbstripout PUBLIC -static)
endif()

install (TARGETS cppnbstripout RUNTIME DESTINATION bin)
