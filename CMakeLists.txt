cmake_minimum_required(VERSION 3.12)
project(vslc)

set(CMAKE_CXX_STANDARD 11)

add_executable(vslc main.cpp lexer/structure/token.cpp lexer/structure/token.h lexer/logic/scanner.cpp lexer/logic/scanner.h utils/cmdline.h utils/source_code_reader.cpp utils/source_code_reader.h)