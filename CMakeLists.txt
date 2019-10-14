cmake_minimum_required(VERSION 3.5)
project (GameThing) #TODO: Change this

if (BUILD_TESTS)
    message(STATUS "BUILD: Test")
    add_definitions(-DTEST)
    file(GLOB_RECURSE TESTS "${PROJECT_SOURCE_DIR}/tests/*.cpp")
else()
    message(STATUS "BUILD: Release")
endif()

# Check submodules
find_package(Git QUIET)
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if (GIT_SUBMODULE)
        message(STATUS "Updating submodules")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive 
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

message(STATUS "Fetching source files")
file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

message(STATUS "Building release")
add_executable(GameThing ${HEADERS} ${SOURCES} ${TESTS})

if (BUILD_TESTS)
    message(STATUS "Adding Catch2 unit test framework")
    add_subdirectory("${PROJECT_SOURCE_DIR}/lib/Catch2")
    target_link_libraries(GameThing Catch2::Catch2)
    list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/lib/Catch2/contrib")

    include(CTest)
    include(Catch)
    catch_discover_tests(GameThing)
endif()