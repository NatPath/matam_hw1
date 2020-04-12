cmake_minimum_required(VERSION 2.6.0)
project(node_test LANGUAGES C)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR})
add_executable(node_test node.c node_test.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)