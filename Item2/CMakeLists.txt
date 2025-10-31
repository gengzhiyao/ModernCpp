add_executable(item2 Item2.cpp)
target_compile_options(item2 PRIVATE $<$<CXX_COMPILER_ID:GNU>:-fpermissive>)  # 仅在 GCC 编译器下生效