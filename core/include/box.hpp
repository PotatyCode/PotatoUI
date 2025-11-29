#pragma once
#include <Rectangle.hpp>
#include <Vector2.hpp>

#include "element.hpp"

namespace potato_ui {
class Box : public Element {
public:
    void render() override;
    Box(Element* parent, raylib::Vector2 dimensions) : Element(parent, dimensions) {};
    ~Box() override = default;
};
}  // namespace potato_ui
