#ifndef FILE_MENU_SCREEN_HPP
#define FILE_MENU_SCREEN_HPP

#include "screen_base.hpp"
#include "screen_helper.hpp"
#include "../program_state.hpp"
#include <ftxui/component/component.hpp>

#include "../file_utils.hpp"

using namespace program_state;
namespace screens {
using namespace ftxui;
    class FileMenuScreen final : public screens::ScreenBase {
    public:
        explicit FileMenuScreen(program_state::ProgramStatePtr program_state) : ScreenBase(std::move(program_state)) {
            PopulateMenu();
        }

        ftxui::Component Render() override {
            auto toolbar = ScreenHelper::GetToolbar();
            auto buttons = ScreenHelper::RenderButtons(file_options_buttons);
            return ftxui::Renderer(file_menu, [toolbar, this] {
                return ftxui::vbox({
                    ftxui::text("File Menu") | bold | ftxui::center,
                    toolbar,
                    RenderMenu(),
                    filler()
                }) | flex;
            });
        }

        bool HandleEvent(ftxui::Event event) override {
            if (file_menu->OnEvent(event)) {
                return true; // Event handled by tool_select_menu
            }
            return false;  // No custom event handling for this screen yet.
        }

    private:
        ftxui::Component file_menu;
        std::vector<Component> file_options_buttons;

        std::string selected_tool = "Brush";
        int size = 1;
        int min_size = 1;
        int max_size = 10;

        Element RenderMenu()
        {
            return vbox({
                file_menu->Render() | flex | border
            }) | center | ftxui::size(WIDTH, GREATER_THAN, 30);
        }

        void PopulateMenu()
        {
            const auto saveButton = Button(constants::saveOptionLabel, [this]{
                //Handle save
                FileUtils::SaveToFile("test.txt", statePtr->canvas->GetPrintable());
            });
            const auto loadButton = Button(constants::loadOptionLabel, [this]{
                //Handle load;
            });
            const auto exitButton = Button(constants::exitLabel, [this]{
                //Handle exit
            });


            file_options_buttons.push_back(saveButton);
            file_options_buttons.push_back(loadButton);
            file_options_buttons.push_back(exitButton);
            file_menu = Container::Vertical(file_options_buttons);
        }
    };
}
#endif // FILE_MENU_SCREEN_HPP
