// main.cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <iostream>
#include <ostream>
#include "screens/screen_manager.hpp"
#include "screens/tool_menu_screen.hpp"
#include "screens/drawing_screen.hpp"
using namespace ftxui;
int main() {
    auto sharedProgramState = std::make_shared<ProgramState>();
    auto cursor = ftxui::Screen::Cursor{.shape = ftxui::Screen::Cursor::Shape::Hidden};
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    screen.SetCursor(cursor);

    screens::ScreenManager screen_manager;

    auto termSize = ftxui::Terminal::Size();

    // Register different screens
    screen_manager.RegisterScreen("ToolMenu", std::make_shared<screens::ToolMenuScreen>(sharedProgramState));
    screen_manager.RegisterScreen("Drawing", std::make_shared<screens::DrawingScreen>(termSize.dimx-2,termSize.dimy-5, sharedProgramState));

    // Start with the Drawing screen
    screen_manager.SwitchTo("Drawing");
    std::cout << "\e[?25l" << std::flush;
    auto renderer = ftxui::Renderer([&] {
        return screen_manager.RenderCurrentScreen()->Render();
    });

    auto event_handler = ftxui::CatchEvent(renderer, [&](ftxui::Event event) {
        if (event == ftxui::Event::F1) {
            screen_manager.SwitchTo("FileMenu");
            return true;
        } else if (event == ftxui::Event::F2) {
            screen_manager.SwitchTo("ToolMenu");
            return true;
        } else if (event == ftxui::Event::F3) {
            screen_manager.SwitchTo("Drawing");
            return true;
        } else if (event == ftxui::Event::F12) {
            screen.Clear();
            screen.Exit();
            return true;
        }

        // Delegate event handling to the current screen
        return screen_manager.HandleCurrentScreenEvent(event);
    });

    screen.Loop(event_handler);
    return 0;
}
