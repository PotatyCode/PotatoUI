#pragma once
#include <memory>
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
    void add_root_element(raylib::Vector2 dimensions) {
        rootElements_.push_back(std::make_unique<T>(&screen_, dimensions));
    }
    ElementManager() {
        add_root_element<Box>({100, 100});
        rootElements_.back()->add_child<Box>({50, 50});
    }
    void render_all();
};

}  // namespace potato_ui
