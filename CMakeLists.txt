cmake_minimum_required(VERSION 3.12)
project(vslc)

set(CMAKE_CXX_STANDARD 11)

if ("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
    message("-- Building project for macOS. Searching for llvm include files in /usr/local/opt/llvm/include")
    if (NOT EXISTS "/usr/local/opt/llvm/include/llvm/ADT/STLExtras.h")
        message(FATAL_ERROR "No llvm include files found in /usr/local/opt/llvm/include.")
    else()
        message("-- [SUCCESS] LLVM include files found")
        set(LLVM_STATIC_INCLUDE "/usr/local/opt/llvm/include")
    endif ()
elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    message("-- Building project for Windows")
    if (NOT EXISTS $ENV{LLVM_PATH}/include)
        message(FATAL_ERROR "No LLVM_PATH environment specified.")
    else()
        set(LLVM_STATIC_INCLUDE $ENV{LLVM_PATH}/llvm/include)
    endif ()
else()
    message(FATAL_ERROR "Unsupported operating system.")
endif ()

include_directories(${LLVM_STATIC_INCLUDE})

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

set(
    source_list
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
)

assign_source_group(${source_list})

add_executable(vslc ${source_list})
