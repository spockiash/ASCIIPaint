#include <ftxui/component/component.hpp>       // for Button, Renderer, Container
#include <ftxui/component/screen_interactive.hpp>  // for ScreenInteractive
#include <ftxui/dom/elements.hpp>  // for text, vbox, border, center, size, WIDTH, color, bgcolor
#include <ftxui/screen/color.hpp>  // for Color
#include <iostream>
#include "paint_tools.hpp"

using namespace ftxui;

// Helper function to render a button for a given ASCII character
Element RenderButton(Component button, char label, Color bg_focus, Color bg_normal) {
    return button->Render() |
           color(Color::White) |
           bgcolor(button->Focused() ? bg_focus : bg_normal) |
           size(WIDTH, EQUAL, 5);  // Width of each button
}


int main() {
    auto screen = ScreenInteractive::Fullscreen();

    // Get all printable ASCII characters
    std::vector<char> ascii_chars = GetAsciiCharacterSet();

    // Create a vector of buttons corresponding to each ASCII character
    std::vector<Component> buttons;
    for (char c : ascii_chars) {
        buttons.push_back(Button(std::string(1, c), [c] {
            std::cout << "Button '" << c << "' clicked.\n";
        }));
    }

    // Create a container for all buttons
    auto button_container = Container::Vertical(buttons);

    // Renderer for the screen with flexible layout
    auto renderer = Renderer(button_container, [&] {
        std::vector<Element> button_elements;
        for (size_t i = 0; i < buttons.size(); ++i) {
            button_elements.push_back(RenderButton(buttons[i], ascii_chars[i], Color::Blue, Color::Black));
        }

        return vbox({
                   flexbox(button_elements) | border | flex // Flex container for buttons
               }) | center;
    });

    screen.Loop(renderer);
    return 0;
}
