#include "../include/element.hpp"

#include <memory>
#include <utility>

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
template <typename T, typename... Args>
void Element::add_child(Args&&... args) {
    childElements_.push_back(std::make_unique<T>(std::forward(args))...);
    childElements_.back()->parent_ = this;
    childElements_.back()->rootElement_ = this->rootElement_;
    if (childElements_.size() == 1) {
        childElements_[0]->dependentElement_ = this;
    }
}
}  // namespace core
