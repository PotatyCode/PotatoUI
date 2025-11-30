#pragma once
#include <Rectangle.hpp>
#include <Vector2.hpp>

#include "element.hpp"

namespace potato_ui {
class Box : public Element {
public:
    Box() = default;
    void render() override;
    ~Box() override = default;
};
}  // namespace potato_ui
