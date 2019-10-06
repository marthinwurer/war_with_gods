cmake_minimum_required(VERSION 3.5)
project (GameThing) # Change this

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TESTS ${PROJECT_SOURCE_DIR}/tests/*.cpp ${PROJECT_SOURCE_DIR}/tests/*.h)

# Testing Framework
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Catch2)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/Catch2/contrib)

add_executable(GameThing ${HEADERS} ${SOURCES} ${TESTS})
target_link_libraries(GameThing Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(GameThing)