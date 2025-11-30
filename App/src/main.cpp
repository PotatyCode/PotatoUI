#include <raylib.h>

#include <Window.hpp>

#include "../../core/include/ElementManager.hpp"

int main() {
    // Window configuration
    const int SCREENWIDTH = 1920 / 2;
    const int SCREENHEIGHT = 1080 / 2;
    potato_ui::ElementManager element_manager;

    raylib::Window window(SCREENWIDTH, SCREENHEIGHT, "Raylib C++ Template");

    // Main game loop
    while (!raylib::Window::ShouldClose()) {
        // Update logic
        element_manager.tile_all();

        // Draw
        BeginDrawing();
        window.ClearBackground(RAYWHITE);
        element_manager.render_all();

        DrawText("Raylib + C++ Template Ready!", 190, 200, 20, LIGHTGRAY);
        DrawFPS(10, 10);

        EndDrawing();
    }

    return 0;
}
