cmake_minimum_required(VERSION 3.0.0)
project(roguelike VERSION 0.1.0)

enable_testing()

find_package(SDL2 CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

file(GLOB_RECURSE SOURCES "app/*.cpp")

add_executable(roguelike main.cpp ${SOURCES})
add_executable(tests_sai SAI/tests/test_main.cpp)
add_executable(tests_vec2d tests/math/tests_vec2d.cpp)

target_link_libraries(roguelike PRIVATE libtcod::libtcod SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(tests_sai PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
target_link_libraries(tests_vec2d PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

target_compile_features(roguelike PRIVATE cxx_std_17)


include(CPack)
include(CTest)
include(Catch)
catch_discover_tests(tests_sai)
