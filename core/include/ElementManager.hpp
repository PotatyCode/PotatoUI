#pragma once
#include <memory>
#include <vector>

#include "element.hpp"
namespace potato_ui {
class ElementManager {
private:
    std::vector<std::unique_ptr<Element>> rootElements_;

public:
    template <typename T, typename... Args>
    void add_root_element(Args&&... args);
};

}  // namespace potato_ui
