#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

void createClass(std::string file) {
  std::ofstream header(file + ".h");
  auto uniqueID = std::chrono::system_clock::now().time_since_epoch().count();
  header << "#pragma once" << std::endl
         << "" << std::endl
         << "class " << file << " {" << std::endl
         << " public:" << std::endl
         << "  " << file << "();" << std::endl
         << " private:" << std::endl
         << "};" << std::endl
         << "" << std::endl;

  std::ofstream source(file + ".cpp");
  source << "#include \"" << file << ".h\"" << std::endl
         << std::endl
         << file << "::" << file << "() {" << std::endl
         <<  std::endl
         << "}" << std::endl;
}

void createMain() {
  boost::filesystem::create_directory("src");
  std::ofstream main("src/main.cpp");
  main << "" << std::endl
       << "int main(int argc, char* argv[]) {" << std::endl
       << std::endl
       << "}" << std::endl;
}

void createReadme() {
  std::ofstream readme("README.md");
  readme << "# OVERVIEW" << std::endl;
}

void createCMake(std::string project) {
  std::ofstream file("CMakeLists.txt");
  file <<
    R"(# CMake settings

cmake_minimum_required(VERSION 2.8.11)

# Project settings

)"
       << "set(PROJECT_NAME " << project << ")" << std::endl
       <<
    R"(project(${PROJECT_NAME})
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
)";
}

void createTest() {
  boost::filesystem::create_directory("test");
  std::ofstream test("test/boost_check.cpp");
  test <<
    R"(#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE boost_check

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( can_build_boost )
{
  BOOST_CHECK(true);
}
)";
}

void createGitIgnore() {
  std::ofstream file(".gitignore");
  file << "# Build files" << std::endl
       << "build/" << std::endl
       << std::endl
       << "# Executables" << std::endl
       << "bin/" << std::endl
       << std::endl
       << "# Platform system files" << std::endl
       << "*.DS_Store" << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc >= 2) {
    if (std::string(argv[1]) == "create") {
      if (argc >= 3) {
        if (std::string(argv[2]) == "class") {
          if (argc == 4) {
            createClass(std::string(argv[3]));
            return 0;
          }
        }
        if (std::string(argv[2]) == "project") {
          if (argc == 4) {
            createCMake(std::string(argv[3]));
            createMain();
            createGitIgnore();
            createReadme();
            createTest();
            return 0;
          }
        }
        if (std::string(argv[2]) == "main") {
          if (argc == 3) {
            createMain();
            return 0;
          }
        }
        if (std::string(argv[2]) == "test") {
            createTest();
            return 0;
        }
        if (std::string(argv[2]) == ".gitIgnore"
            || std::string(argv[2]) == "gitIgnore"
            || std::string(argv[2]) == "gitignore"
            || std::string(argv[2]) == ".gitignore"
            || std::string(argv[2]) == "GitIgnore") {
            createGitIgnore();
            return 0;
        }
        if (std::string(argv[2]) == "CMake"
            || std::string(argv[2]) == "Cmake"
            || std::string(argv[2]) == "cmake") {
          if (argc == 4) {
            createCMake(std::string(argv[3]));
            return 0;
          } else {
            std::cout << "Missing project name" << std::endl;
            return 1;
          }
        }
      }
    }
  }
  std::cout << "Invalid arguments" << std::endl;
  return 1;
}
