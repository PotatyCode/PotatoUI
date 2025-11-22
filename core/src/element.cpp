#include "../include/element.hpp"
#include <Vector2.hpp>

namespace core {
// Core initialization
void element::tileChildren() {
  for (auto &child : childElements) {
    child->position = calcPosition();
    child->tileChildren();
  }
}

raylib::Vector2 element::calcPosition() {
  raylib::Vector2 newPosition;
  if (Parent->childrenHorizental) {
    newPosition.x = dependentElement->position.x + padding.x;
    newPosition.y = Parent->position.y + padding.y;
  }
  return newPosition;
}
} // namespace core
