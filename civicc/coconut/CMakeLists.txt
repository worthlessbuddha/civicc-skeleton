cmake_minimum_required(VERSION 3.13)

project(civicc VERSION 1.0 LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

set(TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/test")
set(COMPILER "${CMAKE_CURRENT_BINARY_DIR}/civicc")

# These will only work after you received the testing framework from us.
enable_testing()
add_test(NAME "basic" COMMAND "${TEST_COMMAND}/run.bash" "${COMPILER}" basic WORKING_DIRECTORY "${TEST_DIR}")
add_test(NAME "nested_funs" COMMAND "${TEST_COMMAND}/run.bash" "${COMPILER}" nested_funs WORKING_DIRECTORY "${TEST_DIR}")
add_test(NAME "arrays" COMMAND "${TEST_COMMAND}/run.bash" "${COMPILER}" arrays WORKING_DIRECTORY "${TEST_DIR}")


find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

bison_target(CivicParser src/scanparse/parser.y "${CMAKE_CURRENT_BINARY_DIR}/parser.c"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/parser.h" VERBOSE)

flex_target(CivicLexer src/scanparse/lexer.l "${CMAKE_CURRENT_BINARY_DIR}/lexer.c"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/lexer.h")
ADD_FLEX_BISON_DEPENDENCY(CivicLexer CivicParser)


if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
        set(BISON_EXECUTABLE "/usr/local/opt/bison/bin/bison")
endif()

include(./coconut/coconut.cmake)

# Whenever you add a file, add it here too.
add_executable(civicc ${FLEX_CivicLexer_OUTPUTS} ${BISON_CivicParser_OUTPUTS}
    src/main.c src/print/print.c src/scanparse/scanParse.c
    src/global/globals.c src/global/globals.h

    src/framework_assignments/strengthreduction.c
    src/framework_assignments/countarithmetic.c
    src/framework_assignments/hashtable.c
)

target_compile_options(civicc PRIVATE
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Wno-unused-function>
)

coconut_target_generate(civicc "${CMAKE_CURRENT_LIST_DIR}/src/main.ccn" dynamic)
target_include_directories(civicc
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/src"
)

add_custom_target(dot
    dot -Tpng ccngen/ast.dot > ast.png
    COMMENT "Generate a png of your ast based on the generated dot diagram."
)
