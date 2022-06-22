cmake_minimum_required(VERSION 3.0.0)
project(roguelike VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SDL2 CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_executable(roguelike main.cpp)
target_link_libraries(roguelike PRIVATE libtcod::libtcod SDL2::SDL2 SDL2::SDL2main)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

include(CPack)