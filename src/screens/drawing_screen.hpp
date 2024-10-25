#ifndef DRAWING_SCREEN_HPP
#define DRAWING_SCREEN_HPP

#include "../draw_canvas/characters.hpp"
#include "screen_base.hpp"
#include "../draw_canvas/draw_canvas.hpp"
#include <iostream>

using namespace ftxui;
using namespace draw_canvas;

namespace screens {
    class DrawingScreen : public screens::ScreenBase {
    public:
        DrawingScreen(int width, int height) : canvas(width,height) {}
        void ResizeCanvas(int width, int height) {

        }
        ftxui::Component Render() override {
            auto matrixContent = canvas.getPrintable();
            auto canvasElements = CanvasToElements(matrixContent);
            auto canvas_display = vbox(canvasElements) | border;

            std::vector<std::string> tools = {"pencil", "line", "circle", "rectangle"};
            int selected = 0;

            // Create tool selector
            auto tool_selector = hbox({
                                     text("Tool: ") | flex,
                                     text(tools[selected]),
                                     separator(),
                                     text("Size: ") | flex,
                                     text("1"),
                                     separator(),
                                     text("F1 - Help")| flex,
                                     separator(),
                                     text("F2 - Pencil")| flex,
                                     separator(),
                                     text("F3 - Line")| flex,
                                     separator(),
                                     text("F4 - Rectangle")| flex,
                                     separator(),
                                     text("F5 - Circle")| flex,
                                     separator(),
                                     text("F9 - Increase")| flex,
                                     separator(),
                                     text("F10 - Decrease")| flex,
                                     separator(),
                                     text("F11 - Save") | flex,
                                     separator(),
                                     text("'q' - Exit") | flex,
                                 }) | border;
            auto selection = &selected_char;

            std::string label = "Click to quit";
            auto button = Button(&label, []{
                exit(0);
            });
            return Renderer(button, [&] {
                return hbox({
                    text("A button:"),
                    button->Render(),
                });
            });

            auto char_select_toolbar = CreateCharSelector();
            return Renderer(btn, [this] {
                return vbox({
                    text("ASCII Canvas Editor v0.01") | bold | center,
                    //tool_selector | size(HEIGHT, EQUAL, 3),
                    //vbox(canvas_display) | flex,
                    btn->Render()
                });
                }
            );
        }

        bool HandleEvent(ftxui::Event event) override {
            // Handle mouse and key events for drawing
            if (event.is_mouse()) {
                auto mouse = event.mouse();

                // Start drawing on mouse press
                if (mouse.button == ftxui::Mouse::Left && mouse.motion == Mouse::Pressed) {
                    is_drawing = true;
                }
                // Stop drawing on release
                else if (mouse.button == Mouse::Left && mouse.motion == Mouse::Released) {
                    is_drawing = false;
                }

                // Only apply drawing if the mouse is moving while the left button is pressed, or
                // if the left button is pressed again (initial drawing point)
                if (is_drawing && (mouse.motion == Mouse::Moved || mouse.motion == Mouse::Pressed)) {
                    // Adjust these offsets based on your UI layout
                    const int HEADER_OFFSET = 1;    // Title
                    const int TOOL_OFFSET = 3;      // Tool selector
                    const int BORDER_OFFSET = 1;    // Border

                    int canvas_x = mouse.x - BORDER_OFFSET;
                    int canvas_y = mouse.y - (HEADER_OFFSET + TOOL_OFFSET + BORDER_OFFSET);

                    // Ensure drawing only happens within the canvas bounds
                    if (canvas_x >= 0 && canvas_x < canvas.getWidth() &&
                        canvas_y >= 0 && canvas_y < canvas.getHeight()) {
                        // Set the character at the current mouse position
                        canvas.setChar(canvas_x, canvas_y, selected_char);

                        // Ask FTXUI to redraw the canvas
                        return true;  // Consume the event, redraw
                    }
                }
            }

            if (event.is_character())
            {

            }

            return false;  // If no drawing occurred, don't consume the event
        }


    private:
        char selected_char = 'a';
        bool is_drawing = false;
        std::vector<Component> buttons;
        draw_canvas::Canvas canvas;
        //Initialize object that holds paintable ASCII characters
        draw_canvas::Characters chars = draw_canvas::Characters();

        Component btn = Button("label", [this]{
            auto x = 1;
            exit(0);
        });

        void SetCharacters(draw_canvas::CharacterSetOptions option)
        {
            chars.SetSelectedOption(option);
        }

        void TestFunc() {
            auto x = 1;
        }
        void Test()
        {
            auto x = 1;
        }
        Element CreateCharSelector()
        {
            auto character_set = chars.GetCharacterSet();

            auto btn = Button("Click Me", [this] { exit(1); });

            // Return the rendered button as an Element
            return RenderCharButton(btn, Color::Blue, Color::Black);
        }
        // Helper function to render a character button
        Element RenderCharButton(Component button, Color bg_focus, Color bg_normal) {
            return button->Render() |
                   color(Color::White) |
                   bgcolor(button->Focused() ? bg_focus : bg_normal) |
                   size(WIDTH, EQUAL, 3);
        }
        // Helper function to convert Canvas lines to FTXUI Elements
        ftxui::Elements CanvasToElements(const std::vector<std::string>& lines) {
            ftxui::Elements elements;
            for (const auto& line : lines) {
                elements.push_back(ftxui::text(line));
            }
            return elements;
        }
    };
}
#endif // DRAWING_SCREEN_HPP
