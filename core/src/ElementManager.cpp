#include "../include/ElementManager.hpp"

#include <memory>
#include <utility>
#include <Vector2.hpp>

namespace potato_ui {
template <typename T>
void ElementManager::add_root_element(raylib::Vector2 dimensions) {
    rootElements_.emplace_back(std::make_unique<T>(&screen_, dimensions));
}
void ElementManager::render_all() {
    for (auto& element : rootElements_) {
        element->render();
        element->render_children();
    }
}
}  // namespace potato_ui
