#!/bin/bash

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Default values
CONFIG="debug"
RUN=false
CLEAN=false

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -r|--release)
            CONFIG="release"
            shift
            ;;
        -d|--debug)
            CONFIG="debug"
            shift
            ;;
        --run)
            RUN=true
            shift
            ;;
        --clean)
            CLEAN=true
            shift
            ;;
        -h|--help)
            echo "Usage: ./build.sh [OPTIONS]"
            echo ""
            echo "Options:"
            echo "  -d, --debug     Build in debug mode (default)"
            echo "  -r, --release   Build in release mode"
            echo "  --run           Run the executable after building"
            echo "  --clean         Clean build artifacts before building"
            echo "  -h, --help      Show this help message"
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            exit 1
            ;;
    esac
done

# Convert config to proper case for premake
if [ "$CONFIG" = "debug" ]; then
    PREMAKE_CONFIG="debug"
    BUILD_CONFIG="Debug"
else
    PREMAKE_CONFIG="release"
    BUILD_CONFIG="Release"
fi

echo -e "${YELLOW}Building in ${BUILD_CONFIG} mode...${NC}"

# Clean if requested
if [ "$CLEAN" = true ]; then
    echo -e "${YELLOW}Cleaning build artifacts...${NC}"
    make clean 2>/dev/null
    rm -rf bin/ bin-int/ obj/ Makefile *.make
    echo -e "${GREEN}Clean complete${NC}"
fi

# Generate makefiles
echo -e "${YELLOW}Generating makefiles...${NC}"
premake5 gmake
if [ $? -ne 0 ]; then
    echo -e "${RED}Premake failed${NC}"
    exit 1
fi

# Build
echo -e "${YELLOW}Compiling...${NC}"
make config=${PREMAKE_CONFIG} -j$(nproc)
if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed${NC}"
    exit 1
fi

echo -e "${GREEN}Build successful!${NC}"

# Determine executable path
SYSTEM=$(uname -s | tr '[:upper:]' '[:lower:]')
EXECUTABLE="bin/${BUILD_CONFIG}-${SYSTEM}-x86_64/App/App"

echo -e "${GREEN}Executable: ${EXECUTABLE}${NC}"

# Run if requested
if [ "$RUN" = true ]; then
    echo -e "${YELLOW}Running application...${NC}"
    echo ""
    ./${EXECUTABLE}
fi
