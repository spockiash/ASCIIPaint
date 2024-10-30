#ifndef TOOL_MENU_SCREEN_HPP
#define TOOL_MENU_SCREEN_HPP

#include "screen_base.hpp"
#include "screen_helper.hpp"
#include "../program_state.hpp"
#include <ftxui/component/component.hpp>

using namespace program_state;
namespace screens {
using namespace ftxui;
    class ToolMenuScreen final : public screens::ScreenBase {
    public:
        explicit ToolMenuScreen(program_state::ProgramStatePtr program_state) : ScreenBase(std::move(program_state)) {
            CreateSizeControls();
            PopulateMenu();
        }

        ftxui::Component Render() override {
            auto toolbar = ScreenHelper::GetToolbar();
            auto buttons = ScreenHelper::RenderButtons(tool_select_buttons);
            return ftxui::Renderer(tool_select_menu, [toolbar, this] {
                return ftxui::vbox({
                    ftxui::text("Tool Menu") | bold | ftxui::center,
                    toolbar,
                    RenderMenu(),
                    filler()
                }) | flex;
            });
        }

        bool HandleEvent(ftxui::Event event) override {
            if(tool_size_menu->OnEvent(event)) {
                return true; // Event handled by tool_size_menu
            }
            if (tool_select_menu->OnEvent(event)) {
                return true; // Event handled by tool_select_menu
            }
            return false;  // No custom event handling for this screen yet.
        }

    private:
        ftxui::Component tool_select_menu;
        std::vector<Component> tool_select_buttons;

        ftxui::Component tool_size_menu;
        std::vector<Component> tool_size_buttons;

        std::string selected_tool = "Brush";
        int size = 1;
        int min_size = 1;
        int max_size = 10;

        Element RenderMenu()
        {
            return vbox({
                text("Size: " + std::to_string(size)),
                vbox({
                    tool_size_menu->Render(),
                }) | flex | border,
                text("Tools:"),
                tool_select_menu->Render() | flex | border
            }) | center | ftxui::size(WIDTH, GREATER_THAN, 30);
        }

        void CreateSizeControls()
        {
            const auto decreaseButton = Button("-", [this]{
                if(size > min_size)
                    size--;
            });

            const auto increaseButton = Button("+", [this]{
                if(size < max_size)
                    size++;
            });

            const auto resetButton = Button("R", [this]{
                size = min_size;
            });

            tool_size_buttons.push_back(decreaseButton);
            tool_size_buttons.push_back(increaseButton);
            tool_size_buttons.push_back(resetButton);

            tool_size_menu = Container::Horizontal(tool_size_buttons);
        }

        void PopulateMenu()
        {
            const auto pencilButton = Button(constants::pencilToolLabel, [this]{
                SelectTool(constants::pencilToolLabel);
            });
            const auto eraserButton = Button(constants::eraserToolLabel, [this]{
                SelectTool(constants::eraserToolLabel);
            });
            const auto circleButton = Button(constants::circleToolLabel, [this]{
                SelectTool(constants::circleToolLabel);
            });
            const auto patternButton = Button(constants::patternToolLabel, [this]{
                SelectTool(constants::patternToolLabel);
            });

            tool_select_buttons.push_back(pencilButton);
            tool_select_buttons.push_back(eraserButton);
            tool_select_buttons.push_back(circleButton);
            tool_select_buttons.push_back(patternButton);
            tool_select_menu = Container::Vertical(tool_select_buttons);
        }

        void SelectTool(const std::string& tool_name) {
            auto it = statePtr->tools.find(tool_name);
            if (it != statePtr->tools.end()) {
                statePtr->current_tool = it->second();
            }
        }
    };
}
#endif // TOOL_MENU_SCREEN_HPP
