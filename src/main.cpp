// main.cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "screens/screen_manager.hpp"
#include "screens/tool_menu_screen.hpp"
#include "screens/drawing_screen.hpp"

int main() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screens::ScreenManager screen_manager;

    // Register different screens
    screen_manager.RegisterScreen("ToolMenu", std::make_shared<screens::ToolMenuScreen>());
    screen_manager.RegisterScreen("Drawing", std::make_shared<screens::DrawingScreen>());

    // Start with the Drawing screen
    screen_manager.SwitchTo("Drawing");

    auto renderer = ftxui::Renderer([&] {
        return screen_manager.RenderCurrentScreen()->Render();
    });

    auto event_handler = ftxui::CatchEvent(renderer, [&](ftxui::Event event) {
        if (event == ftxui::Event::F1) {
            screen_manager.SwitchTo("ToolMenu");
            return true;
        } else if (event == ftxui::Event::F2) {
            screen_manager.SwitchTo("Drawing");
            return true;
        }

        // Delegate event handling to the current screen
        return screen_manager.HandleCurrentScreenEvent(event);
    });

    screen.Loop(event_handler);
    return 0;
}
