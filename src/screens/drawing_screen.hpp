#ifndef DRAWING_SCREEN_HPP
#define DRAWING_SCREEN_HPP

#include "screen_base.hpp"
#include "../draw_canvas/draw_canvas.hpp"

using namespace ftxui;
using namespace draw_canvas;

namespace screens {
    class DrawingScreen : public screens::ScreenBase {
    public:
        DrawingScreen() : canvas(30,30) {}
        ftxui::Component Render() override {
            auto matrixContent = canvas.getPrintable();
            auto elements = CanvasToElements(matrixContent);
            return Renderer([elements] {
                return vbox({
                    text("ASCII Canvas Editor v0.01"),
                    vbox(elements) | border
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
            return false;
        }

    private:
        char selected_char = 'c';
        bool is_drawing = false;
        draw_canvas::Canvas canvas;
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
