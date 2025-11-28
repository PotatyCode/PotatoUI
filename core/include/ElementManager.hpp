#pragma once
#include <memory>
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
    template <typename T, typename... Args>
    void add_root_element(Args&&... args);
    ElementManager() { add_root_element<Box>({100, 100}); }
    void render_all();
};

}  // namespace potato_ui
