
add_subdirectory(string_utilities)

add_library(area area.c AreaNode.c)
target_link_libraries(area PUBLIC string_utilities)
target_include_directories(area PUBLIC
 "${CMAKE_CURRENT_BINARY_DIR}"
 "${CMAKE_CURRENT_SOURCE_DIR}/string_utilities"
)