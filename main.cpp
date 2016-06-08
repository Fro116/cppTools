#include <iostream>
#include <fstream>
#include <chrono>

void createClass(std::string file) {
  std::ofstream header(file + ".h");
  auto uniqueID = std::chrono::system_clock::now().time_since_epoch().count();
  header << "#ifndef " << file << "_" << uniqueID << std::endl;
  header << "#define " << file << "_" << uniqueID << std::endl;
  header << "" << std::endl;
  header << "#include <iostream>" << std::endl;
  header << "#include <string>" << std::endl;
  header << "#include <fstream>" << std::endl;
  header << "#include <vector>" << std::endl;
  header << "#include <algorithm>" << std::endl;
  header << "#include <sstream>" << std::endl;
  header << "#include <memory>" << std::endl;
  header << "#include <cassert>" << std::endl;
  header << "#include <limits>" << std::endl;
  header << "#include <chrono>" << std::endl;
  header << "" << std::endl;
  header << "class " << file << " {" << std::endl;
  header << " public:" << std::endl;
  header << " private:" << std::endl;
  header << "};" << std::endl;
  header << "" << std::endl;
  header << "#endif" << std::endl;

  std::ofstream source(file + ".cpp");
  source << "#include \"" << file << ".h\"" << std::endl;
  source << "" << std::endl;
  source << file << "::" << file << "() {" << std::endl; 
  source << "}" << std::endl;
}

void createMain() {
  std::ofstream main("main.cpp");
  main << "#include <iostream>" << std::endl;
  main << "#include <string>" << std::endl;
  main << "#include <fstream>" << std::endl;
  main << "#include <vector>" << std::endl;
  main << "#include <algorithm>" << std::endl;
  main << "#include <sstream>" << std::endl;
  main << "#include <memory>" << std::endl;
  main << "#include <cassert>" << std::endl;
  main << "#include <limits>" << std::endl;
  main << "#include <chrono>" << std::endl;
  main << "" << std::endl;
  main << "int main(int argc, char* argv[]) {" << std::endl;
  main << "" << std::endl;
  main << "}" << std::endl;
}

void createCMake(std::string project) {
  std::ofstream file("CMakeLists.txt");
  file << "cmake_minimum_required(VERSION 2.8.11)" << std::endl;
  file << "project(" << project << ")" << std::endl;
  file << "add_executable (" << project << " main.cpp)" << std::endl;
  file << "SET(CMAKE_CXX_FLAGS \"-std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused\")" << std::endl;
}

void createGitIgnore(std::string project) {
  std::ofstream file(".gitignore");
  file << "#build files" << std::endl;
  file << "CMake*" << std::endl;
  file << "Makefile" << std::endl;
  file << "*.o" << std::endl;
  file << project << std::endl;
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
	    createGitIgnore(std::string(argv[3]));
	    return 0;
	  }
	}
	if (std::string(argv[2]) == "main") {
	  if (argc == 3) {
	    createMain();
	    return 0;
	  }
	}
	if (std::string(argv[2]) == ".gitIgnore" || std::string(argv[2]) == "gitIgnore" || std::string(argv[2]) == "gitignore"
	    || std::string(argv[2]) == ".gitignore" || std::string(argv[2]) == "GitIgnore") {
	  if (argc == 4) {
	    createGitIgnore(argv[3]);
	    return 0;
	  }
	}
	if (std::string(argv[2]) == "CMake" || std::string(argv[2]) == "Cmake" || std::string(argv[2]) == "cmake") {
	  if (argc == 4) {
	    createCMake(std::string(argv[3]));
	    return 0;
	  }
	}
      }
    }
  }
  std::cout << "Invalid arguments" << std::endl;
}