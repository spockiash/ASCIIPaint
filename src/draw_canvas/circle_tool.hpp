//
// Created by bobo on 29.10.24.
//
// ReSharper disable CppUseStructuredBinding
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
                if (canvas_x >= 0 && canvas_x < canvas.GetWidth() &&
                    canvas_y >= 0 && canvas_y < canvas.GetHeight()) {
                    center_x = canvas_x;
                    center_y = canvas_y;
                    is_drawing = true;
                    last_radius = 0;
                    //At the start of drawing, create snapshot of current matrix content
                    canvas.CreateSnapshot();
                    return true;
                }
            }
            // Update circle on mouse move
            else if (is_drawing && mouse.motion == ftxui::Mouse::Moved) {
                if (canvas_x >= 0 && canvas_x < canvas.GetWidth() &&
                    canvas_y >= 0 && canvas_y < canvas.GetHeight()) {
                    // Calculate radius
                    const int dx = canvas_x - center_x;
                    const int dy = canvas_y - center_y;
                    // ReSharper disable once CppTooWideScopeInitStatement
                    const int new_radius = static_cast<int>(std::sqrt(dx * dx + dy * dy));

                    // Only redraw if radius has changed
                    if (new_radius != last_radius) {
                        DrawCircle(canvas, center_x, center_y, new_radius);
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
        int tolerance = 2;
        double y_scale = 0.55f;

        void DrawCircle(Canvas& canvas, const int cx, const int cy, const int radius) const {
            //reset to snapshot before each circle draw
            canvas.RevertSnapshot();

            auto circlePoints = CalculateCirclePoints(cx, cy, radius);
            //ApplyYScale(circlePoints, y_scale);
            PlotCircle(circlePoints, canvas);
        }

        [[nodiscard]] std::vector<std::pair<int, int>> CalculateCirclePoints(const int h, const int k, const int r) const {
            std::vector<std::pair<int, int>> points;
            //define square bounds
            int x = 0;
            int y = r;
            int d = 1 - r; // Initial decision variable

            // Loop until we cross the diagonal (x > y)
            while (x <= y) {
                // Scale y by y_scale to account for aspect ratio
                int scaled_y = static_cast<int>(y * y_scale);

                // Plot points in each of the 8 octants
                points.push_back({h + x, k + scaled_y}); // Octant 1
                points.push_back({h - x, k + scaled_y}); // Octant 2
                points.push_back({h + x, k - scaled_y}); // Octant 3
                points.push_back({h - x, k - scaled_y}); // Octant 4

                points.push_back({h + y, k + static_cast<int>(x * y_scale)}); // Octant 5
                points.push_back({h - y, k + static_cast<int>(x * y_scale)}); // Octant 6
                points.push_back({h + y, k - static_cast<int>(x * y_scale)}); // Octant 7
                points.push_back({h - y, k - static_cast<int>(x * y_scale)}); // Octant 8

                // Update the decision variable based on the midpoint
                if (d < 0) {
                    // Midpoint is inside the circle, go horizontally (x++)
                    d += 2 * x + 3;
                } else {
                    // Midpoint is outside or on the circle, go diagonally (x++, y--)
                    d += 2 * (x - y) + 5;
                    y--;
                }
                x++;
            }
            return points;
        }

        static void ApplyYScale(std::vector<std::pair<int, int>>& points, const double y_scale) {
            for (auto& point : points) {
                point.second = static_cast<int>(point.second * y_scale); // scale y-coordinate
            }
        }

        void PlotCircle(std::vector<std::pair<int, int>>& points, Canvas& canvas) const {
            const int height = canvas.GetHeight();
            const int width = canvas.GetWidth();
            for (const auto& point : points) {
                const int x = point.first;
                // ReSharper disable once CppTooWideScopeInitStatement
                const int y = point.second;

                // Ensure (x, y) is within canvas bounds
                if (x >= 0 && x < width && y >= 0 && y < height) {
                    canvas.SetChar(x, y, selected_char); // Plot character
                }
            }
        }


    };
}

#endif // CIRCLE_TOOL_HPP
