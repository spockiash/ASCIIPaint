#include <ftxui/component/component.hpp>       // for Button, Renderer, Container
#include <ftxui/component/screen_interactive.hpp>  // for ScreenInteractive
#include <ftxui/dom/elements.hpp>  // for text, vbox, border, center, size, WIDTH, color, bgcolor
#include <ftxui/screen/color.hpp>  // for Color
#include <iostream>
#include "paint_tools.hpp"
#include "ftxui/dom/canvas.hpp"


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
    auto c = Canvas(100, 100);
    auto drawnChar = std::string("c");

    c.DrawText(2, 2, drawnChar);

    auto element = canvas(&c);

    // Renderer for the screen with flexible layout
    auto renderer = Renderer([&] {

        return element | border;
    });

    auto component = CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse() && event.mouse().Left) {
            int x = event.mouse().x;
            int y = event.mouse().y;
            int b = 1;
            // Check if the mouse coordinates are within canvas bounds
            if (x >= 0 && x < 100 && y >= 0 && y < 100) {
                // Clear the canvas

                // Draw the character 't' at the mouse position
                c.DrawText(x, y, drawnChar);

                // Request a redraw of the canvas
                screen.PostEvent(Event::Custom);
            }
            return true;
        }
        return false;
    });

    screen.Loop(component);
    return 0;
}
