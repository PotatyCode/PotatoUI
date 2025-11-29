#pragma once
#include <Touch.hpp>
#include <Vector2.hpp>

#include "../include/element.hpp"
namespace potato_ui {
class Screen : public Element {
private:
    raylib::Vector2 ScreenSize_;

public:
    Screen(raylib::Vector2 screen_size = {1080, 1920})
        : Element{nullptr, screen_size}, ScreenSize_{screen_size} {}
    ~Screen() override = default;
    void render() override {};
};
}  // namespace potato_ui
