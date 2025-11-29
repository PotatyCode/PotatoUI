#include "../include/ElementManager.hpp"

#include <memory>
#include <Vector2.hpp>

#include "../include/element.hpp"

namespace potato_ui {
void ElementManager::render_all() {
    for (auto& element : rootElements_) {
        element->render();
        element->render_children();
    }
}
}  // namespace potato_ui
