#pragma once
#include <memory>
#include <vector>

#include "element.hpp"
#include "Screen.hpp"
namespace potato_ui {
class ElementManager {
private:
    std::vector<std::unique_ptr<Element>> rootElements_;
    Screen screen_;

public:
    template <typename T, typename... Args>
    void add_root_element(Args&&... args);
};

}  // namespace potato_ui
