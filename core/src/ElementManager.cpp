#include "../include/ElementManager.hpp"

#include <memory>
#include <utility>

namespace potato_ui {
template <typename T, typename... Args>
void ElementManager::add_root_element(Args&&... args) {
    rootElements_.emplace_back(std::make_unique<T>(screen_, std::forward<Args>(args))...);
}
void ElementManager::render_all() {
    for (auto& element : rootElements_) {
        element->render();
        element->render_children();
    }
}
}  // namespace potato_ui
