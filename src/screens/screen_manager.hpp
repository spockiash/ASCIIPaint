// screen_manager.hpp
#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "screen_base.hpp"
#include <memory>
#include <map>

namespace screens {
    class ScreenManager {
    public:
        void RegisterScreen(const std::string& name, std::shared_ptr<ScreenBase> screen) {
            screens[name] = screen;
        }

        void SwitchTo(const std::string& name) {
            if (screens.find(name) != screens.end()) {
                current_screen = screens[name];
            }
        }

        ftxui::Component RenderCurrentScreen() {
            if (current_screen) {
                return current_screen->Render();
            }
            return ftxui::Renderer([] { return ftxui::text("No screen selected"); });
        }

        bool HandleCurrentScreenEvent(ftxui::Event event) {
            if (current_screen) {
                return current_screen->HandleEvent(event);
            }
            return false;
        }

    private:
        std::map<std::string, std::shared_ptr<ScreenBase>> screens;
        std::shared_ptr<ScreenBase> current_screen;
    };
}
#endif  // SCREEN_MANAGER_HPP
