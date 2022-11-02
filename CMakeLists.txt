cmake_minimum_required(VERSION 3.0.0)
project(roguelike VERSION 0.1.0)

enable_testing()

find_package(SDL2 CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

file(GLOB_RECURSE SOURCES "roguelike/*.cpp")
file(COPY "roguelike/data" DESTINATION "${CMAKE_BINARY_DIR}/Debug")

add_executable(roguelike main.cpp ${SOURCES})
add_executable(tests_sai SAI/tests/test_main.cpp)
add_executable(tests_vec2d tests/math/tests_vec2d.cpp)
add_executable(tests_world tests/tests_world.cpp ${SOURCES})
add_executable(tests_threading tests/tests_threading.cpp)
add_executable(tests_message_router tests/tests_message_router.cpp ${SOURCES})
add_executable(tests_rendering tests/tests_rendering.cpp ${SOURCES})
add_executable(tests_yaml tests/tests_yaml.cpp ${SOURCES})

target_link_libraries(roguelike PRIVATE libtcod::libtcod SDL2::SDL2 SDL2::SDL2main yaml-cpp)
target_link_libraries(tests_sai PRIVATE Catch2::Catch2 Catch2::Catch2WithMain yaml-cpp)
target_link_libraries(tests_vec2d PRIVATE Catch2::Catch2 Catch2::Catch2WithMain yaml-cpp)
target_link_libraries(tests_world PRIVATE libtcod::libtcod SDL2::SDL2 Catch2::Catch2 Catch2::Catch2WithMain yaml-cpp)
target_link_libraries(tests_threading PRIVATE Catch2::Catch2 Catch2::Catch2WithMain yaml-cpp)
target_link_libraries(tests_message_router PRIVATE libtcod::libtcod Catch2::Catch2 Catch2::Catch2WithMain yaml-cpp)
target_link_libraries(tests_rendering PRIVATE libtcod::libtcod SDL2::SDL2 Catch2::Catch2 Catch2::Catch2WithMain yaml-cpp)
target_link_libraries(tests_yaml PRIVATE Catch2::Catch2 Catch2::Catch2WithMain yaml-cpp libtcod::libtcod)

target_compile_features(roguelike PRIVATE cxx_std_17)
target_compile_features(tests_world PRIVATE cxx_std_17)
target_compile_features(tests_threading PRIVATE cxx_std_17)
target_compile_features(tests_message_router PRIVATE cxx_std_17)
target_compile_features(tests_rendering PRIVATE cxx_std_17)
target_compile_features(tests_yaml PRIVATE cxx_std_17)


include(CPack)
include(CTest)
include(Catch)
catch_discover_tests(tests_sai)
catch_discover_tests(tests_vec2d)
catch_discover_tests(tests_world)
catch_discover_tests(tests_threading)
catch_discover_tests(tests_message_router)
catch_discover_tests(tests_rendering)
catch_discover_tests(tests_yaml)

