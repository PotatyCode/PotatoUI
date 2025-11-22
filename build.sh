#!/bin/bash

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Default to debug if no argument provided
BUILD_TYPE="${1:-debug}"

# Normalize build type
BUILD_TYPE=$(echo "$BUILD_TYPE" | tr '[:upper:]' '[:lower:]')

# Validate build type
if [ "$BUILD_TYPE" != "debug" ] && [ "$BUILD_TYPE" != "release" ]; then
    echo -e "${RED}Error: Invalid build type '$1'${NC}"
    echo "Usage: ./build.sh [debug|release]"
    exit 1
fi

# Convert to CMake format
if [ "$BUILD_TYPE" = "debug" ]; then
    CMAKE_BUILD_TYPE="Debug"
else
    CMAKE_BUILD_TYPE="Release"
fi

echo "==================================="
echo "  Building in $CMAKE_BUILD_TYPE mode"
echo "==================================="
echo ""

# Check dependencies
echo "Checking dependencies..."
if ! command -v cmake &> /dev/null; then
    echo -e "${RED}Error: cmake not found. Install with: sudo pacman -S cmake${NC}"
    exit 1
fi

if ! pacman -Qi raylib &> /dev/null; then
    echo -e "${RED}Error: raylib not found. Install with: sudo pacman -S raylib${NC}"
    exit 1
fi

if ! yay -Qi raylib-cpp &> /dev/null 2>&1; then
    echo -e "${YELLOW}Warning: raylib-cpp not found. Install with: yay -S raylib-cpp${NC}"
    echo "Attempting to continue..."
fi

# Create build directory
BUILD_DIR="build"
mkdir -p "$BUILD_DIR"

# Configure with CMake
echo ""
echo "Configuring CMake..."
cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE"

# Build
echo ""
echo "Building project..."
cmake --build "$BUILD_DIR" -j$(nproc)

echo ""
echo "==================================="
echo -e "${GREEN}✓ Build completed successfully!${NC}"
echo "==================================="
echo ""
echo "Executable location: $BUILD_DIR/bin/"
echo "Library location: $BUILD_DIR/lib/"
echo ""

# Find and display the executable name
EXECUTABLE=$(find "$BUILD_DIR/bin" -type f -executable 2>/dev/null | head -1)
if [ -n "$EXECUTABLE" ]; then
  ./$EXECUTABLE
fi

