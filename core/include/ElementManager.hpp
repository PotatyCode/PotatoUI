#pragma once
#include <memory>
#include <vector>

#include "element.hpp"
namespace potato_ui {
class ElementManager {
private:
    std::vector<std::unique_ptr<Element>> rootElements_;
};
}  // namespace potato_ui
