#pragma once
// Core library header
#include <raylib.h>

#include <Color.hpp>
#include <memory>
#include <optional>
#include <Rectangle.hpp>
#include <Vector2.hpp>
#include <vector>
namespace potato_ui {

class Element {
protected:
    std::optional<raylib::Vector2> dimensions_;
    raylib::Vector2 position_{0, 0};
    raylib::Vector2 padding_{0, 0};
    raylib::Color bgColor_{WHITE};
    std::vector<std::unique_ptr<Element>> childElements_;
    bool childrenHorizental_ = true;

    Element* dependentElement_ = nullptr;
    Element* const PARENT;
    Element* const ROOTPARENT;

public:
    explicit Element(Element* parent, raylib::Vector2 dimensions);
    virtual ~Element() = default;
    Element(const Element&) = delete;
    Element& operator=(const Element&) = delete;
    Element(Element&&) = default;
    Element& operator=(Element&&) = delete;

    void tile_children();
    raylib::Vector2 calc_position();
    std::optional<raylib::Vector2> calc_furthest_point();
    void update_parent_dimension();
    template <typename T, typename... Args>
    void add_child(Args&&... args);
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
