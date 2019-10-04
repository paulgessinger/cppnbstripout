cmake_minimum_required(VERSION 3.11)

project(cppnbstripout LANGUAGES CXX)
enable_testing()

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

add_library(cppnbstripoutlib STATIC src/cppnbstripoutlib.cpp)
target_compile_features(cppnbstripoutlib PUBLIC cxx_std_17)
target_link_libraries(cppnbstripoutlib PRIVATE nlohmann_json::nlohmann_json)

add_executable(cppnbstripout src/cppnbstripout.cpp)
target_compile_features(cppnbstripout PUBLIC cxx_std_17)
target_link_libraries(cppnbstripout PRIVATE nlohmann_json::nlohmann_json cppnbstripoutlib)

include(GoogleTest)
find_package(GTest REQUIRED)

add_executable(test_cppnbstripout src/test_cppnbstripout.cpp)
target_compile_features(test_cppnbstripout PUBLIC cxx_std_17)
target_link_libraries(test_cppnbstripout ${GTEST_LIBRARIES} cppnbstripoutlib nlohmann_json::nlohmann_json)

gtest_discover_tests(test_cppnbstripout)

# statically linked executables do not work on macOS
if(NOT APPLE)
  target_link_libraries(cppnbstripout PUBLIC -static)
endif()

install (TARGETS cppnbstripout RUNTIME DESTINATION bin)
