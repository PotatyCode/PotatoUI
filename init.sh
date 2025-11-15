#!/bin/bash

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${YELLOW}Raylib C++ Project Initialization${NC}"
echo ""

# Get project name
read -p "Enter project name (e.g., MyGame): " PROJECT_NAME

if [ -z "$PROJECT_NAME" ]; then
    echo -e "${RED}Project name cannot be empty${NC}"
    exit 1
fi

echo ""
echo -e "${YELLOW}Renaming project to: ${PROJECT_NAME}${NC}"

# Replace in premake5.lua
sed -i "s/workspace \"RaylibProject\"/workspace \"$PROJECT_NAME\"/g" premake5.lua

echo -e "${GREEN}✓ Updated premake5.lua${NC}"

# Initialize git submodules
echo ""
echo -e "${YELLOW}Initializing submodules (raylib + raylib-cpp)...${NC}"
git submodule update --init --recursive

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Submodules initialized${NC}"
else
    echo -e "${RED}✗ Failed to initialize submodules${NC}"
    echo "You may need to add them manually:"
    echo "  git submodule add https://github.com/raysan5/raylib vendor/raylib"
    echo "  git submodule add https://github.com/RobLoach/raylib-cpp vendor/raylib-cpp"
fi

rm -rf vendor/raylib/.git
rm -rf vendor/raylib/examples
rm -rf vendor/raylib/parser
rm -rf vendor/raylib/projects
rm -rf vendor/raylib/logo
rm -rf vendor/raylib/.github
rm -rf vendor/raylib/cmake
rm -f vendor/raylib/*.zig
rm -f vendor/raylib/CMakeLists.txt

# Clean raylib-cpp
rm -rf vendor/raylib-cpp/.git
rm -rf vendor/raylib-cpp/examples
rm -rf vendor/raylib-cpp/projects
rm -rf vendor/raylib-cpp/tests
rm -rf vendor/raylib-cpp/.github
rm -f vendor/raylib-cpp/CMakeLists.txt
# Make build script executable
chmod +x build.sh

echo ""
echo -e "${GREEN}✓ Project initialized!${NC}"
echo ""
echo "Next steps:"
echo "  1. Run: ./build.sh"
echo "  2. Start coding in Core/src/ and App/src/"
echo ""
echo -e "${YELLOW}Note: You can delete init.sh now if you want.${NC}"
