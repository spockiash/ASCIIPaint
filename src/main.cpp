// main.cpp
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "draw_canvas/draw_canvas.hpp"

using namespace ftxui;
using namespace draw_canvas;

// Helper function to convert Canvas lines to FTXUI Elements
Elements CanvasToElements(const std::vector<std::string>& lines) {
    Elements elements;
    for (const auto& line : lines) {
        elements.push_back(text(line));
    }
    return elements;
}

// Helper function to render a character button
Element RenderCharButton(Component button, char label, Color bg_focus, Color bg_normal) {
    return button->Render() |
           color(Color::White) |
           bgcolor(button->Focused() ? bg_focus : bg_normal) |
           size(WIDTH, EQUAL, 3);
}

int main() {
    auto screen = ScreenInteractive::Fullscreen();

    // Initialize canvas
    auto canvas = draw_canvas::Canvas(30, 30);

    // Create some initial content
    canvas.setChar(0, 0, 'a');
    canvas.setChar(1, 1, 'b');
    canvas.setChar(2, 2, 'C');
    canvas.setChar(3, 3, 'd');
    canvas.setChar(4, 4, 'e');
    canvas.setChar(5, 5, 'f');

    // Create commonly used ASCII characters for buttons
    std::vector<char> chars = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z', '#', '@', '*', '.'
    };

    // Create character buttons
    std::vector<Component> buttons;
    char selected_char = 'a';  // Default character to draw

    for (char c : chars) {
        buttons.push_back(Button(std::string(1, c), [&selected_char, c] {
            selected_char = c;
        }));
    }

    // Create button container
    auto button_container = Container::Horizontal(buttons);

    // Main component with canvas display
    auto main_container = Container::Vertical({
        button_container,
    });

    // Renderer that combines everything
    auto renderer = Renderer(main_container, [&] {
        // Get current canvas content
        auto lines = canvas.getPrintable();

        // Create canvas display elements
        auto canvas_display = vbox(CanvasToElements(lines)) | border;

        // Create button elements
        std::vector<Element> button_elements;
        for (size_t i = 0; i < buttons.size(); ++i) {
            button_elements.push_back(
                RenderCharButton(buttons[i], chars[i], Color::Blue, Color::Black)
                );
        }
        auto button_row = hbox(button_elements) | border;

        // Combine everything into final layout
        return vbox({
            text("ASCII Canvas Editor") | bold | center,
            button_row | size(HEIGHT, EQUAL, 3),
            canvas_display | flex,
            text("Selected char: " + std::string(1, selected_char)) | center
        });
    });

    bool is_drawing = false;

    // Add canvas interaction
    auto canvas_component = CatchEvent(renderer, [&](Event event) {
        if (event.is_mouse()) {
            auto mouse = event.mouse();

            // Start drawing on mouse press
            if (mouse.button == Mouse::Left && mouse.motion == Mouse::Pressed) {
                is_drawing = true;
            }
            // Stop drawing on release
            else if (mouse.button == Mouse::Left && mouse.motion == Mouse::Released) {
                is_drawing = false;
            }

            if ((is_drawing && mouse.motion == Mouse::Moved) ||
                (mouse.button == Mouse::Left && mouse.motion == Mouse::Pressed)) {
                // Convert screen coordinates to canvas coordinates
                // Note: You might need to adjust these calculations based on your layout
                int canvas_x = mouse.x - 1;  // Adjust for border
                int canvas_y = mouse.y - 5;  // Adjust for header and buttons
                if (canvas_x >= 0 && canvas_x < 80 && canvas_y >= 0 && canvas_y < 80) {
                    canvas.setChar(canvas_x, canvas_y, selected_char);
                    return true;
                }
            }
        }
        return false;
    });

    screen.Loop(canvas_component);
    return 0;
}
