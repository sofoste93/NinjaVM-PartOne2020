cmake_minimum_required(VERSION 3.16)
project(NinjaVM VERSION 4.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(njvm
    src/main.c
    src/vm.c
)
target_include_directories(njvm PRIVATE include)

if(MSVC)
    target_compile_options(njvm PRIVATE /W4)
else()
    target_compile_options(njvm PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
if(BUILD_TESTING)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
    add_test(NAME cli_version COMMAND njvm --version)
    set_tests_properties(cli_version PROPERTIES PASS_REGULAR_EXPRESSION "4.1.0")
    add_test(
        NAME vm_integration
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_cli.py
                $<TARGET_FILE:njvm> ${CMAKE_CURRENT_BINARY_DIR}/test-data
    )
endif()

install(TARGETS njvm RUNTIME DESTINATION bin)
