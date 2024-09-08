project(DataStructures)

file(GLOB_RECURSE bst_src "bst/*.c" "bst/*.h")
add_executable(bst ${bst_src})

file(GLOB_RECURSE heap_src "heap/*.c" "heap/*.h")
add_executable(heap ${heap_src})