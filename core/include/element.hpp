#pragma once
// Core library header
#include <memory>
#include <optional>
#include <raylib-cpp.hpp>
#include <Vector2.hpp>
#include <vector>
// Add your library interfaces here
namespace core {
class Element {
private:
    std::optional<raylib::Vector2> dimensions_;
    raylib::Vector2 position_;
    raylib::Vector2 padding_ = {0, 0};
    raylib::Rectangle bounds_;
    std::optional<raylib::Color> bgColor_;
    std::vector<std::unique_ptr<Element>> childElements_;
    bool childrenHorizental_ = true;

    Element* dependentElement_;
    Element* parent_;
    Element* rootElement_;

public:
    Element();
    void tile_children();
    raylib::Vector2 calc_position();
    raylib::Vector2 update_dimension();

    // GETTERS
    bool is_children_horizontal() const { return childrenHorizental_; }
    raylib::Vector2 get_position() { return position_; }
};
}  // namespace core
