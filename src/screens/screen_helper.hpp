/*********************************************
*               ScreenHelper.hpp             *
 *                                           *
 * Author: Bobo                              *
 * Date:   28.10.2024                        *
 * Description: Helper functions for rende-  *
 * ring stuff using FTXUI lib                *
 *                                           *
 *********************************************/

#ifndef SCREENHELPER_H
#define SCREENHELPER_H
#include "ftxui/dom/elements.hpp"
#include "../constants.hpp"
#include <ftxui/component/component_base.hpp>
namespace screens {
    using namespace ftxui;
    class ScreenHelper {
    public:
        //Helper function that creates toolbar for screens
        static ftxui::Element GetToolbar()
        {
            return hbox(
                   filler(), //blank component to center the content
                   flex_grow(text(constants::fileOptionLabel)) | color(Color::Green) | bold,
                   flex_grow(text(constants::toolsOptionLabel)) | color(Color::Green) | bold,
                   flex_grow(text(constants::saveOptionLabel)) | color(Color::Green) | bold,
                   flex_grow(text(constants::loadOptionLabel)) | color(Color::Green) | bold,
                   flex_grow(text(constants::exitOptionLabel)) | color(Color::Green) | bold
                   ) | ftxui::flex;
        }

        // Helper function to convert Canvas lines to FTXUI Elements
        static ftxui::Elements CanvasToElements(const std::vector<std::string>& lines) {
            ftxui::Elements elements;
            for (const auto& line : lines) {
                elements.push_back(ftxui::text(line));
            }
            return elements;
        }

        //Helper wrapper function to create vector of rendered elements
        static std::vector<Element> RenderCharButtons(std::vector<Component>& buttons, std::vector<char>& char_set)
        {
            std::vector<Element> button_elements;
            for (size_t i = 0; i < buttons.size(); ++i) {
                button_elements.push_back(
                    RenderCharButton(buttons[i], char_set[i], Color::Blue, Color::Black)
                    );
            }
            return button_elements;
        }

        // Helper function to render a character button
        static Element RenderCharButton(Component button, char label, Color bg_focus, Color bg_normal) {
            return button->Render() |
                   color(Color::White) |
                   bgcolor(button->Focused() ? bg_focus : bg_normal) |
                   size(WIDTH, EQUAL, 3);
        }


    private:
        ScreenHelper() = default;
    };
}
#endif //SCREENHELPER_H
