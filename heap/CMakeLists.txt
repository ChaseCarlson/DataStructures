project(heap)

file(GLOB_RECURSE heap_src "*.c" "*.h")
add_executable(heap ${heap_src})