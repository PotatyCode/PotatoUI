#include <raylib.h>

#include <raylib-cpp.hpp>

int main() {
    // Window configuration
    const int SCREENWIDTH = 1920 / 2;
    const int screenHeight = 1080 / 2;

    raylib::Window window(SCREENWIDTH




    , screenHeight, "Raylib C++ Template");

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
