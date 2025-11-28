#include "../include/box.hpp"

#include <raylib.h>

#include <Rectangle.hpp>
namespace potato_ui {
void Box::render() {
    raylib::Rectangle bounds{get_bounds()};
    bounds.Draw(bgColor_);
}
}  // namespace potato_ui
