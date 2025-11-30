#pragma once
#include <memory>
#include <string>
#include <type_traits>
#include <Vector2.hpp>
#include <vector>

#include "box.hpp"
#include "element.hpp"
#include "Screen.hpp"
namespace potato_ui {
class ElementManager {
private:
    std::vector<std::unique_ptr<Element>> rootElements_;
    Screen screen_;

public:
    template <typename T>
    void add_root_element(const std::string& name, raylib::Vector2 dimensions) {
        static_assert(std::is_base_of<Element, T>(),
                      "root element must be a class derived from Element");
        auto& new_root = rootElements_.emplace_back(std::make_unique<T>());
        new_root.get()->init(&screen_, name, dimensions, &screen_);
    }
    ElementManager() {
        add_root_element<Box>("Root Box", {100, 100});
        rootElements_.back()->add_child<Box>("Child Box", {50, 50});
    }
    void render_all();
    void tile_all();
};

}  // namespace potato_ui
