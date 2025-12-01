#include "../include/element.hpp"

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <Vector2.hpp>

namespace potato_ui {
void Element::init(Element* parent,
                   std::string name,
                   raylib::Vector2 dimensions,
                   Element* dependent_element) {
    parent_ = parent;
    name_ = std::move(name);
    dimensions_ = dimensions;
    dependentElement_ = dependent_element;
}
void Element::tile_children() {
    if (childElements_.size() != 0) {
        for (auto& child : childElements_) {
            child->position_ = child->calc_position();
            child->tile_children();
        }
    } else {
        update_parent_dimension();
    }
}
raylib::Vector2 Element::calc_position() {
    raylib::Vector2 new_position;
    if (parent_->is_children_horizontal()) {
        new_position.x = dependentElement_->position_.x + padding_.x;
        new_position.y = parent_->position_.y + padding_.y;
    } else {
        new_position.x = parent_->position_.y + padding_.y;
        new_position.y = dependentElement_->position_.y + padding_.y;
    }
    return new_position;
}
// Throws nullopt if dimensions_ not calculated
std::optional<raylib::Vector2> Element::calc_furthest_point() {
    if (dimensions_) {
        return raylib::Vector2{position_.x + dimensions_.value().x + padding_.x,
                               position_.y + dimensions_.value().y + padding_.y};
    }
    return std::nullopt;
}

void Element::update_parent_dimension() {
    if (!parent_->dimensions_) {
        parent_->dimensions_ = *dimensions_ + padding_;
        parent_->update_parent_dimension();
    }
    auto furthest_point = calc_furthest_point();
    auto parent_furthest_point = parent_->calc_furthest_point();
    if (furthest_point->x > parent_furthest_point->x) {
        parent_->dimensions_->x = furthest_point->x - parent_->position_.x - parent_->padding_.x;
    }
    if (furthest_point->y > parent_furthest_point->y) {
        parent_->dimensions_->x = furthest_point->y;
    }
}

void Element::render_children() {
    for (auto& element : childElements_) {
        element->render();
        element->render_children();
    }
}
}  // namespace potato_ui
