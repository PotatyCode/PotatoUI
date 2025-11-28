#include "../include/ElementManager.hpp"

#include <memory>
#include <utility>

namespace potato_ui {
template <typename T, typename... Args>
void ElementManager::add_root_element(Args&&... args) {
    rootElements_.emplace_back(std::make_unique<T>(screen_, std::forward<Args>(args))...);
}
}  // namespace potato_ui
