# CMake settings

cmake_minimum_required(VERSION 2.8.11)

# Project settings

set(PROJECT_NAME cppTools)
project(${PROJECT_NAME})
SET(CMAKE_CXX_FLAGS "-std=c++14 -pedantic -Wall -Wextra -Wcast-align \
                    -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization \
                    -Wformat=2 -Winit-self -Wmissing-declarations \
                    -Wmissing-include-dirs -Wold-style-cast \
                    -Woverloaded-virtual -Wredundant-decls -Wshadow \
                    -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 \
                    -Wswitch-default -Wundef -Wno-unused -Werror \
                    -Wno-unused-parameter")

# Main executable

add_executable(${PROJECT_NAME} src/main.cpp)
find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                      ${CMAKE_CURRENT_SOURCE_DIR}/bin/release)

# BOOST tests

enable_testing()
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Create test cases

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
foreach(testSrc ${TEST_SRCS})
        get_filename_component(testName ${testSrc} NAME_WE)
        add_executable(${testName} ${testSrc})
        target_link_libraries(${testName} ${Boost_LIBRARIES})

        #I like to move testing binaries into a testBin directory
        set_target_properties(${testName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin/test)

        #Finally add it to test execution -
        #Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${testName}
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/test
                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/bin/test/${testName} )
endforeach(testSrc)
