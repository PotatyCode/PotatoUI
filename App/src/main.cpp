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
