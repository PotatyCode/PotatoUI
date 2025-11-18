#!/bin/bash

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "==================================="
echo "  Cleaning build artifacts"
echo "==================================="
echo ""

# Check if build directory exists
if [ ! -d "build" ]; then
    echo -e "${YELLOW}Nothing to clean: build directory doesn't exist${NC}"
    exit 0
fi

# Confirm deletion
read -p "Remove build directory and all artifacts? (y/N): " -n 1 -r
echo ""

if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo "Clean cancelled"
    exit 0
fi

# Remove build directory
echo "Removing build directory..."
rm -rf build

# Remove CMake generated files in source tree (if any)
if [ -f "CMakeCache.txt" ]; then
    echo "Removing CMakeCache.txt..."
    rm -f CMakeCache.txt
fi

if [ -d "CMakeFiles" ]; then
    echo "Removing CMakeFiles directory..."
    rm -rf CMakeFiles
fi

if [ -f "cmake_install.cmake" ]; then
    echo "Removing cmake_install.cmake..."
    rm -f cmake_install.cmake
fi

if [ -f "compile_commands.json" ]; then
    echo "Removing compile_commands.json..."
    rm -f compile_commands.json
fi

echo ""
echo "==================================="
echo -e "${GREEN}✓ Clean completed successfully!${NC}"
echo "==================================="
echo ""
echo "Run './build.sh debug' or './build.sh release' to rebuild"
echo ""
