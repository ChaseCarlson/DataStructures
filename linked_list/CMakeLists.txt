project(linked_list)

file(GLOB_RECURSE linked_list_src "*.c" "*.h")
add_executable(linked_list ${linked_list_src})