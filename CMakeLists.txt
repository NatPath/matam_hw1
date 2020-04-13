cmake_minimum_required(VERSION 2.8.0)
project(map_test LANGUAGE C)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR})
add_executable(map_test ./map/pairnode.c ./map/map.c ./map/map_test.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
