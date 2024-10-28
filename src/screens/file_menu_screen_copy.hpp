#ifndef FILE_MENU_SCREEN_COPY_H
#define FILE_MENU_SCREEN_COPY_H

#include "screen_base.hpp"
#include <ftxui/component/component.hpp>
#include "screen_helper.hpp"
namespace screens {
using namespace ftxui;
    class FileMenuScreen : public screens::ScreenBase {
    public:
        FileMenuScreen() {
            tool_menu = ftxui::Container::Vertical({
                ftxui::Button("Save", [] { /* handle pencil selection */ }),
                ftxui::Button("Load", [] { /* handle brush selection */ }),
                ftxui::Button("Exit", [] { /* handle eraser selection */ })
            });
        }

        ftxui::Component Render() override {
            auto toolbar = ScreenHelper::GetToolbar();

            return ftxui::Renderer(tool_menu, [toolbar, this] {
                return ftxui::vbox({
                    ftxui::text("File Menu") | bold | ftxui::center ,
                    toolbar,
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
#endif // FILE_MENU_SCREEN_COPY_H
