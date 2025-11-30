#pragma once
#include <Rectangle.hpp>
#include <string>
#include <utility>
#include <Vector2.hpp>

#include "element.hpp"

namespace potato_ui {
class Box : public Element {
public:
    void render() override;
    Box(Element* parent, std::string name, raylib::Vector2 dimensions)
        : Element(parent, std::move(name), dimensions) {};
    ~Box() override = default;
};
}  // namespace potato_ui
