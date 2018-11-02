cmake_minimum_required(VERSION 3.11)
project(vslc)

set(CMAKE_CXX_STANDARD 11)

function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

set(source_list
        "main.cpp"
        "lexical/structure/token.cpp"
        "lexical/structure/token.h"
        "lexical/logic/scanner.cpp"
        "lexical/logic/scanner.h"
        "utils/cmdline.h"
        "utils/source_code_reader.cpp"
        "utils/source_code_reader.h"
        "syntax/structure/ast.h"
        "syntax/structure/ast.cpp"
        "syntax/logic/parser.cpp"
        "syntax/logic/parser.h"
        "syntax/structure/parsing_table.h"
        "syntax/structure/parsing_stack.cpp"
        "syntax/structure/parsing_stack.h"
        "syntax/structure/input_buffer.cpp"
        "syntax/structure/input_buffer.h"
        "syntax/structure/production.cpp"
        "syntax/structure/production.h"
        "syntax/structure/symbol.cpp"
        "syntax/structure/symbol.h"
        "syntax/structure/parsing_table.cpp"
        utils/shortcuts.h utils/shortcuts.cpp)

assign_source_group(${source_list})

add_executable(vslc ${source_list})

# SECTION LLVM_CONFIG
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Find the libraries that correspond to the LLVM components that we wish to use
llvm_map_components_to_libnames(llvm_libs
        support core irreader executionengine interpreter
        mc mcjit bitwriter x86codegen target)

# Link against LLVM libraries
target_link_libraries(vslc ${llvm_libs})
# END SECTION