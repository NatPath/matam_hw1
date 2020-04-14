cmake_minimum_required(VERSION 3.0.0)
project(map_test LANGUAGES C)

include(CTest)

include_directories(${PROJECT_SOURCE_DIR}/map ${PROJECT_SOURCE_DIR}/map/pairnode)
add_executable(map_test ./map/pairnode/pairnode.c ./map/map.c ./map/map_test.c )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)




