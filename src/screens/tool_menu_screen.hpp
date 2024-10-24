#ifndef TOOL_MENU_SCREEN_HPP
#define TOOL_MENU_SCREEN_HPP

#include "screen_base.hpp"
#include <ftxui/component/component.hpp>
namespace screens {
    class ToolMenuScreen : public screens::ScreenBase {
    public:
        ToolMenuScreen() {
            tool_menu = ftxui::Container::Vertical({
                ftxui::Button("Pencil", [] { /* handle pencil selection */ }),
                ftxui::Button("Brush", [] { /* handle brush selection */ }),
                ftxui::Button("Eraser", [] { /* handle eraser selection */ })
            });
        }

        ftxui::Component Render() override {
            return ftxui::Renderer(tool_menu, [this] {
                return ftxui::vbox({
                    ftxui::text("Tool Menu") | ftxui::center,
                    tool_menu->Render() | ftxui::center
                });
            });
        }

        bool HandleEvent(ftxui::Event event) override {
            return false;  // No custom event handling for this screen yet.
        }

    private:
        ftxui::Component tool_menu;
    };
}
#endif // TOOL_MENU_SCREEN_HPP
