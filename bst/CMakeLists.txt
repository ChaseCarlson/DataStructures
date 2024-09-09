project(bst)

file(GLOB_RECURSE bst_src "*.c" "*.h")
add_executable(bst ${bst_src})