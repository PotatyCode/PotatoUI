#pragma once
// Core library header
#include <Vector2.hpp>
#include <memory>
#include <raylib-cpp.hpp>
#include <raylib.h>
#include <vector>
// Add your library interfaces here
namespace core {
class element {
private:
  raylib::Vector2 dimensions;
  raylib::Vector2 position;
  raylib::Vector2 padding;
  raylib::Rectangle bounds;
  raylib::Color bgColor;
  std::vector<std::unique_ptr<element>> childElements;
  bool childrenHorizental = true;

  element *dependentElement;
  element *Parent;
  element *RootElement;

  // GETTERS
  bool isChildrenHorizontal() { return childrenHorizental; }

public:
  void tileChildren();
  raylib::Vector2 calcPosition();
};
} // namespace core
