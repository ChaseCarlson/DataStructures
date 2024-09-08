project(DataStructures)

file(GLOB_RECURSE bst_src "bst/*.c" "bst/*.h")
add_executable(bst ${bst_src})