//
// Created by bobo on 29.10.24.
//
#ifndef CIRCLE_TOOL_HPP
#define CIRCLE_TOOL_HPP

#include "tool_base.hpp"
#include "../constants.hpp"
#include <cmath>

namespace draw_canvas {
    class CircleTool final : public ToolBase {
    public:
        ~CircleTool() override = default;

        bool HandleEvent(const ftxui::Mouse& mouse, Canvas& canvas) override {
            const int canvas_x = mouse.x - BORDER_OFFSET;
            const int canvas_y = mouse.y - (HEADER_OFFSET + TOOL_OFFSET + BORDER_OFFSET);

            // Start drawing on mouse press - set center point
            if (mouse.button == ftxui::Mouse::Left && mouse.motion == ftxui::Mouse::Pressed) {
                if (canvas_x >= 0 && canvas_x < canvas.getWidth() &&
                    canvas_y >= 0 && canvas_y < canvas.getHeight()) {
                    center_x = canvas_x;
                    center_y = canvas_y;
                    is_drawing = true;
                    last_radius = 0;
                    return true;
                }
            }
            // Update circle on mouse move
            else if (is_drawing && mouse.motion == ftxui::Mouse::Moved) {
                if (canvas_x >= 0 && canvas_x < canvas.getWidth() &&
                    canvas_y >= 0 && canvas_y < canvas.getHeight()) {
                    // Calculate radius
                    int dx = canvas_x - center_x;
                    int dy = canvas_y - center_y;
                    int new_radius = static_cast<int>(std::sqrt(dx * dx + dy * dy));

                    // Only redraw if radius has changed
                    if (new_radius != last_radius) {
                        drawCircle(canvas, center_x, center_y, new_radius);
                        last_radius = new_radius;
                        return true;
                    }
                }
            }
            // Finish drawing on mouse release
            else if (mouse.button == ftxui::Mouse::Left && mouse.motion == ftxui::Mouse::Released) {
                is_drawing = false;
            }

            return false;
        }

        [[nodiscard]] const char* GetName() const override {
            return constants::circleToolLabel;
        }

    private:
        int center_x = 0;
        int center_y = 0;
        int last_radius = 0;

        void drawCircle(Canvas& canvas, int cx, int cy, int radius) {
            // Clear previous circle by filling with spaces
            for (int y = 0; y < canvas.getHeight(); ++y) {
                for (int x = 0; x < canvas.getWidth(); ++x) {
                    canvas.setChar(x, y, ' ');
                }
            }

            // Draw new circle using Bresenham's circle algorithm
            int x = radius;
            int y = 0;
            int error = 0;

            while (x >= y) {
                plotCirclePoints(canvas, cx, cy, x, y);
                plotCirclePoints(canvas, cx, cy, y, x);

                y++;
                error += 1 + 2 * y;
                if (2 * (error - x) + 1 > 0) {
                    x--;
                    error += 1 - 2 * x;
                }
            }
        }

        void plotCirclePoints(Canvas& canvas, int cx, int cy, int x, int y) {
            // Plot points in all octants
            plotPoint(canvas, cx + x, cy + y);
            plotPoint(canvas, cx - x, cy + y);
            plotPoint(canvas, cx + x, cy - y);
            plotPoint(canvas, cx - x, cy - y);
            plotPoint(canvas, cx + y, cy + x);
            plotPoint(canvas, cx - y, cy + x);
            plotPoint(canvas, cx + y, cy - x);
            plotPoint(canvas, cx - y, cy - x);
        }

        void plotPoint(Canvas& canvas, int x, int y) {
            if (x >= 0 && x < canvas.getWidth() &&
                y >= 0 && y < canvas.getHeight()) {
                canvas.setChar(x, y, selected_char);
            }
        }
    };
}

#endif // CIRCLE_TOOL_HPP
