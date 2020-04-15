cmake_minimum_required(VERSION 3.0.0)
project(election_check LANGUAGE C)

include(CTest)
enable_testing()

add_executable(election_check ./ex1/libmap_for_csl3/libmap.a ./election/election.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
