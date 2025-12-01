#!/bin/bash

echo "========================================="
echo "    Bubble Sort Mini-Project Experiments"
echo "========================================="
echo ""

echo "1. Building all targets..."
make clean > /dev/null 2>&1
make all
echo "   Done!"
echo ""

echo "2. Running basic benchmark (n=5000)..."
echo "----------------------------------------"
./bubble_O2 5000
echo ""

echo "3. Compiler optimization comparison..."
echo "----------------------------------------"
make compare
echo ""

echo "4. Running detailed analysis..."
echo "----------------------------------------"
./analyze
echo ""

echo "5. Performance counter analysis..."
echo "----------------------------------------"
echo "Basic (Random data):"
./bubble_O2 5000 0 > /dev/null 2>&1
make perf-basic 2>&1 | grep -E "branches|branch-misses"
echo ""

echo "Early Stop (Sorted data - change to sorted):"

echo "(Run manually with sorted data for accurate comparison)"
echo ""

echo "6. Assembly analysis..."
echo "----------------------------------------"
make assembly
echo ""

