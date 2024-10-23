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

    std::vector<std::string> tools = {"pencil", "line", "circle", "rectangle"};
    int selected = 0;

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

    // Create dropdown component
    auto dropdown = Dropdown(&tools, &selected);

    // Main component with canvas display - Include both button_container and dropdown
    auto main_container = Container::Vertical({
        dropdown,
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

        // Create tool selector
        auto tool_selector = hbox({
                                 text("Tool: ") | vcenter,
                                 text(tools[selected]),
                             }) | border;

        // Combine everything into final layout
        return vbox({
            text("ASCII Canvas Editor") | bold | center,
            tool_selector | size(HEIGHT, EQUAL, 3),
            canvas_display | flex,
            button_row,
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
                // Adjust these offsets based on your UI layout
                const int HEADER_OFFSET = 2;    // Title
                const int TOOL_OFFSET = 3;      // Tool selector
                const int BORDER_OFFSET = 1;    // Border

                int canvas_x = mouse.x - BORDER_OFFSET;
                int canvas_y = mouse.y - (HEADER_OFFSET + TOOL_OFFSET + BORDER_OFFSET);

                if (canvas_x >= 0 && canvas_x < 30 && canvas_y >= 0 && canvas_y < 30) {
                    canvas.setChar(canvas_x, canvas_y, selected_char);
                    return true;
                }
            }
        }

        if (event.is_character())
        {
            //Draw pencil tool
            if(event == Event::p)
            {
                selected = 0;
            }
            //Draw line tool
            if(event == Event::l)
            {
                selected = 1;
            }
            //Draw circle tool
            if(event == Event::c)
            {
                selected = 2;
            }
            //Draw rectangle tool
            if(event == Event::r)
            {
                selected = 3;
            }
            //Save
            if(event == Event::s)
            {
                selected = 1;
            }
        }

        return false;
    });

    screen.Loop(canvas_component);
    return 0;
}
