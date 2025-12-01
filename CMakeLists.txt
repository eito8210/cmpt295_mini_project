cmake_minimum_required(VERSION 3.10)
project(BubbleSort C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(BUBBLE_SRCS bubble_sorts.c benchmark.c)
set(ANALYZE_SRCS bubble_sorts.c analysis.c)

add_executable(bubble_O0 ${BUBBLE_SRCS})
target_compile_options(bubble_O0 PRIVATE -O0)

add_executable(bubble_O2 ${BUBBLE_SRCS})
target_compile_options(bubble_O2 PRIVATE -O2)

add_executable(bubble_O3 ${BUBBLE_SRCS})
target_compile_options(bubble_O3 PRIVATE -O3 -march=native)

add_executable(analyze ${ANALYZE_SRCS})
target_compile_options(analyze PRIVATE -O2)


add_custom_target(compare
    COMMAND echo "=== Optimization Level Impact ==="
    COMMAND echo "Testing Basic implementation on Random data n=5000"
    COMMAND echo ""
    COMMAND echo "-O0:"
    COMMAND ./bubble_O0 5000 0
    COMMAND echo ""
    COMMAND echo "-O2:"
    COMMAND ./bubble_O2 5000 0
    COMMAND echo ""
    COMMAND echo "-O3:"
    COMMAND ./bubble_O3 5000 0
    DEPENDS bubble_O0 bubble_O2 bubble_O3
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Comparing optimization levels"
)

add_custom_target(perf-basic
    COMMAND echo "=== Performance Counters: Basic Implementation ==="
    COMMAND perf stat -e cycles,instructions,branches,branch-misses ./bubble_O2 5000 0
    DEPENDS bubble_O2
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running perf analysis on Basic implementation"
)

add_custom_target(perf-early
    COMMAND echo "=== Performance Counters: Early Stop Implementation ==="
    COMMAND perf stat -e cycles,instructions,branches,branch-misses ./bubble_O2 5000 1
    DEPENDS bubble_O2
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running perf analysis on Early Stop implementation"
)

add_custom_target(perf-branchless
    COMMAND echo "=== Performance Counters: Branchless Implementation ==="
    COMMAND perf stat -e cycles,instructions,branches,branch-misses ./bubble_O2 5000 2
    DEPENDS bubble_O2
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running perf analysis on Branchless implementation"
)

add_custom_target(perf-all
    COMMAND echo "=== Performance Counters: All Implementations ==="
    COMMAND perf stat -e cycles,instructions,branches,branch-misses,L1-dcache-loads,L1-dcache-load-misses ./bubble_O2 5000
    DEPENDS bubble_O2
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running perf analysis on all implementations"
)

add_custom_target(assembly
    COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -O2 -S ${CMAKE_SOURCE_DIR}/bubble_sorts.c -o bubble_sorts.s
    COMMAND echo "Generated bubble_sorts.s"
    COMMAND echo ""
    COMMAND echo "Checking for optimization patterns:"
    COMMAND sh -c "echo -n '  cmov instructions (branchless): '; grep -c 'cmov' bubble_sorts.s || echo '0'"
    COMMAND sh -c "echo -n '  Loop unrolling: '; grep -c '\\.L[0-9]*:' bubble_sorts.s"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating and analyzing assembly code"
)

add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove bubble_O0 bubble_O2 bubble_O3 analyze *.s *.o
    COMMENT "Cleaning all generated files"
)