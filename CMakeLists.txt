cmake_minimum_required(VERSION 3.11)

project(cppnbstripout LANGUAGES CXX)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

add_executable(cppnbstripout cppnbstripout.cpp)
target_compile_features(cppnbstripout PUBLIC cxx_std_17)
target_link_libraries(cppnbstripout PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(cppnbstripout PUBLIC -static)
