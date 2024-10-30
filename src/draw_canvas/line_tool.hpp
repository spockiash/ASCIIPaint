//
// Created by bobo on 29.10.24.
//
// ReSharper disable CppUseStructuredBinding
#ifndef LINE_TOOL_HPP
#define LINE_TOOL_HPP

#include "tool_base.hpp"
#include "../constants.hpp"
#include <cmath>

namespace draw_canvas {
    class LineTool final : public ToolBase {
    public:
        ~LineTool() override = default;

        bool HandleEvent(const ftxui::Mouse& mouse, Canvas& canvas) override {
            const int canvas_x = mouse.x - BORDER_OFFSET;
            const int canvas_y = mouse.y - (HEADER_OFFSET + TOOL_OFFSET + BORDER_OFFSET);

            // Start drawing on mouse press - set starting point
            if (mouse.button == ftxui::Mouse::Left && mouse.motion == ftxui::Mouse::Pressed) {
                if (canvas_x >= 0 && canvas_x < canvas.GetWidth() &&
                    canvas_y >= 0 && canvas_y < canvas.GetHeight()) {
                    start_x = canvas_x;
                    start_y = canvas_y;
                    is_drawing = true;
                    canvas.CreateSnapshot();  // Create snapshot at start of drawing
                    return true;
                }
            }
            // Update line on mouse move
            else if (is_drawing && mouse.motion == ftxui::Mouse::Moved) {
                if (canvas_x >= 0 && canvas_x < canvas.GetWidth() &&
                    canvas_y >= 0 && canvas_y < canvas.GetHeight()) {
                    DrawLine(canvas, start_x, start_y, canvas_x, canvas_y);
                    return true;
                }
            }
            // Finish drawing on mouse release
            else if (mouse.button == ftxui::Mouse::Left && mouse.motion == ftxui::Mouse::Released) {
                is_drawing = false;
            }

            return false;
        }

        [[nodiscard]] const char* GetName() const override {
            return constants::lineToolLabel;
        }

    private:
        int start_x = 0;  // Start point x-coordinate
        int start_y = 0;  // Start point y-coordinate

        // Draws the line based on the start and current points
        void DrawLine(Canvas& canvas, const int x1, const int y1, const int x2, const int y2) const {
            // Revert to snapshot before each line draw
            canvas.RevertSnapshot();

            auto linePoints = CalculateLinePoints(x1, y1, x2, y2);
            PlotLine(linePoints, canvas);
        }

        // Calculate points along the line using Bresenham's algorithm
        [[nodiscard]] std::vector<std::pair<int, int>> CalculateLinePoints(const int x1, const int y1, const int x2, const int y2) const {
            std::vector<std::pair<int, int>> points;

            int dx = std::abs(x2 - x1);
            int dy = std::abs(y2 - y1);
            int sx = (x1 < x2) ? 1 : -1;
            int sy = (y1 < y2) ? 1 : -1;

            int err = dx - dy;
            int x = x1;
            int y = y1;

            // Loop to generate points along the line
            while (true) {
                points.push_back({x, y});  // Add the current point

                // Break when we reach the endpoint
                if (x == x2 && y == y2) break;

                int e2 = 2 * err;

                // Adjust x-coordinate
                if (e2 > -dy) {
                    err -= dy;
                    x += sx;
                }

                // Adjust y-coordinate
                if (e2 < dx) {
                    err += dx;
                    y += sy;
                }
            }

            return points;
        }

        // Plot each point in the line on the canvas
        void PlotLine(const std::vector<std::pair<int, int>>& points, Canvas& canvas) const {
            const int height = canvas.GetHeight();
            const int width = canvas.GetWidth();

            for (const auto& point : points) {
                const int x = point.first;
                const int y = point.second;

                // Ensure (x, y) is within canvas bounds
                if (x >= 0 && x < width && y >= 0 && y < height) {
                    canvas.SetChar(x, y, selected_char);  // Plot character
                }
            }
        }
    };
}

#endif // LINE_TOOL_HPP
