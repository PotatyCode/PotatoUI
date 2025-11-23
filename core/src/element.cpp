#include "../include/element.hpp"

namespace core {
// Core initialization
Element::Element() {}
void Element::tile_children() {
    for (auto& child : childElements_) {
        child->position_ = calc_position();
        child->tile_children();
    }
}

raylib::Vector2 Element::calc_position() {
    raylib::Vector2 new_position;
    if (parent_->is_children_horizontal()) {
        new_position.x = dependentElement_->position_.x + padding_.x;
        new_position.y = parent_->position_.y + padding_.y;
    }
    return new_position;
}
raylib::Vector2 Element::update_dimension() {}
}  // namespace core
