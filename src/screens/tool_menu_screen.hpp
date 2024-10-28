#ifndef TOOL_MENU_SCREEN_HPP
#define TOOL_MENU_SCREEN_HPP

#include "screen_base.hpp"
#include "screen_helper.hpp"
#include <ftxui/component/component.hpp>
namespace screens {
using namespace ftxui;
    class ToolMenuScreen : public screens::ScreenBase {
    public:
        ToolMenuScreen() {
            PopulateMenu();
        }

        ftxui::Component Render() override {
            auto toolbar = ScreenHelper::GetToolbar();
            auto buttons = ScreenHelper::RenderButtons(menu_buttons);
            return ftxui::Renderer(tool_menu, [toolbar, buttons, this] {
                return ftxui::vbox({
                    ftxui::text("Tool Menu") | bold | ftxui::center,
                    toolbar,
                    ftxui::text(std::to_string(size)),
                    yflex_grow(tool_menu->Render() | border | ftxui::size(WIDTH, ftxui::GREATER_THAN, 25) |center),
                    filler()
                }) | flex;
            });
        }

        bool HandleEvent(ftxui::Event event) override {
            return tool_menu->OnEvent(event);
            return false;  // No custom event handling for this screen yet.
        }

    private:
        ftxui::Component tool_menu;
        std::vector<Component> menu_buttons;
        std::string selected_tool = "Brush";
        int size = 1;
        void PopulateMenu()
        {
            auto slider = Slider("Size", &size, 1, 10, 1);
            auto brushButton = Button("Brush", [this]{
                selected_tool = "Brush";
            });
            auto eraserButton = Button("Eraser", [this]{
                selected_tool = "Eraser";
            });
            auto lineButton = Button("Line", [this]{
                selected_tool = "Line";
            });

            menu_buttons.push_back(slider);
            menu_buttons.push_back(brushButton);
            menu_buttons.push_back(eraserButton);
            menu_buttons.push_back(lineButton);

            tool_menu = Container::Vertical(menu_buttons);
        }
    };
}
#endif // TOOL_MENU_SCREEN_HPP
