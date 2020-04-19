cmake_minimum_required(VERSION 3.0.0)
project(election_test C)

include(CTest)
enable_testing()

add_subdirectory(map)
SET_TARGET_PROPERTIES(map PROPERTIES LINKER_LANGUAGE C)
add_subdirectory(area)


add_executable(election_test election.c election_test.c)
target_link_libraries(election_test PUBLIC map)
target_link_libraries(election_test PUBLIC area)


target_include_directories(election_test PUBLIC
 "${PROJECT_BINARY_DIR}"
 "${PROJECT_SOURCE_DIR}/map"
 "${PROJECT_SOURCE_DIR}/area"
 )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
