#!/bin/bash

set -e

echo "==================================="
echo "  Raylib C++ Project Initializer"
echo "==================================="
echo ""


# Prompt for project name
read -p "Enter project name (no spaces): " PROJECT_NAME

# Validate project name
if [ -z "$PROJECT_NAME" ]; then
    echo "Error: Project name cannot be empty"
    exit 1
fi

if [[ "$PROJECT_NAME" =~ [[:space:]] ]]; then
    echo "Error: Project name cannot contain spaces"
    exit 1
fi

echo ""
echo "Initializing project: $PROJECT_NAME"
echo ""

# Create directory structure

# Create template main.cpp
echo "Generating template main.cpp..."
cat > App/src/main.cpp << 'EOF'
#include <raylib-cpp.hpp>

int main() {
    // Window configuration
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    raylib::Window window(screenWidth, screenHeight, "Raylib C++ Template");
    window.SetTargetFPS(60);
    
    // Main game loop
    while (!window.ShouldClose()) {
        // Update logic
        
        // Draw
        BeginDrawing();
        window.ClearBackground(RAYWHITE);
        
        DrawText("Raylib + C++ Template Ready!", 190, 200, 20, LIGHTGRAY);
        DrawFPS(10, 10);
        
        EndDrawing();
    }
    
    return 0;
}
EOF

# Create placeholder files for core library
echo "Creating core library placeholders..."
cat > core/include/core.hpp << 'EOF'
#pragma once

// Core library header
// Add your library interfaces here

namespace core {
    void init();
}
EOF

cat > core/src/core.cpp << 'EOF'
#include "core.hpp"

namespace core {
    void init() {
        // Core initialization
    }
}
EOF

# Check if CMakeLists.txt exists
if [ ! -f "CMakeLists.txt" ]; then
    echo "Error: CMakeLists.txt not found in current directory"
    exit 1
fi

# Replace project name in CMakeLists.txt
echo "Configuring CMakeLists.txt..."
sed -i "s/__PROJECT_NAME__/$PROJECT_NAME/g" CMakeLists.txt

# Initialize git if not already done
if [ ! -d ".git" ]; then
    echo "Initializing git repository..."
    git init
    
    # Create .gitignore
    cat > .gitignore << 'EOF'
# Build directories
build/
cmake-build-*/

# IDE
.vscode/
.idea/
*.swp
*.swo
*~

# Compiled files
*.o
*.a
*.so
*.dylib

# Executables
bin/

# CMake
CMakeCache.txt
CMakeFiles/
cmake_install.cmake
compile_commands.json

# OS
.DS_Store
Thumbs.db
EOF
    
    git add .gitignore
    echo "Git repository initialized"
fi

echo ""
echo "==================================="
echo "✓ Project '$PROJECT_NAME' initialized successfully!"
echo "==================================="
echo ""
echo "Next steps:"
echo "  1. Review and edit App/src/main.cpp"
echo "  2. Run './build.sh debug' to build in debug mode"
echo "  3. Run './build.sh release' to build in release mode"
echo "  4. Your executable will be in build/bin/$PROJECT_NAME"
echo ""
