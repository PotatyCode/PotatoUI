#pragma once
// Core library header
#include <raylib.h>

#include <Color.hpp>
#include <iostream>
#include <memory>
#include <optional>
#include <Rectangle.hpp>
#include <string>
#include <type_traits>
#include <Vector2.hpp>
#include <vector>
namespace potato_ui {

class Element {
protected:
    std::string name_;
    std::optional<raylib::Vector2> dimensions_;
    raylib::Vector2 position_{0, 0};
    raylib::Vector2 padding_{0, 0};
    raylib::Color bgColor_{WHITE};
    std::vector<std::unique_ptr<Element>> childElements_;
    bool childrenHorizental_ = true;

    Element* dependentElement_ = nullptr;
    Element* parent_ = nullptr;
    Element* rootParent_ = nullptr;

public:
    explicit Element();
    void init(Element* parent, std::string name, raylib::Vector2 dimensions);
    virtual ~Element() = default;
    Element(const Element&) = delete;
    Element& operator=(const Element&) = delete;
    Element(Element&&) = default;
    Element& operator=(Element&&) = delete;

    void tile_children();
    raylib::Vector2 calc_position();
    std::optional<raylib::Vector2> calc_furthest_point();
    void update_parent_dimension();

    template <typename T>
    void add_child(std::string name, raylib::Vector2 dimensions) {
        static_assert(std::is_base_of<Element, T>(), "child must be of base class element");
        auto& new_child = childElements_.emplace_back(std::make_unique<T>(this, name, dimensions));
        if (childElements_.size() == 1) {  // basically if this is the first child
            new_child->dependentElement_ = this;
            dimensions_ = std::nullopt;
        } else {
            childElements_.back()->dependentElement_ =
                childElements_[childElements_.size() - 2].get();
        }
    }

    virtual void render() = 0;
    void render_children();

    // GETTERS
    bool is_children_horizontal() const { return childrenHorizental_; }
    raylib::Vector2 get_position() const { return position_; }
    raylib::Rectangle get_bounds() const {
        return {position_.x, position_.y, dimensions_->x, dimensions_->y};
    }
};
}  // namespace potato_ui
