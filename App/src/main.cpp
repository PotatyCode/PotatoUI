#include <raylib-cpp.hpp>

int main() {
  // Window configuration
  const int screenWidth = 1920 / 2;
  const int screenHeight = 1080 / 2;

  raylib::Window window(screenWidth, screenHeight, "Raylib C++ Template");

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
