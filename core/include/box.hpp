#pragma once
#include <Rectangle.hpp>
#include <Vector2.hpp>

#include "element.hpp"

namespace potato_ui {
class Box : Element {
public:
    void render() override;
    Box(Element* parent, raylib::Vector2 dimensions);
    ~Box() override = default;
};
}  // namespace potato_ui
