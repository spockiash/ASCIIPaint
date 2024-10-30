#ifndef PATTERN_TOOL_HPP
#define PATTERN_TOOL_HPP

#include "tool_base.hpp"
#include "../constants.hpp"
#include <cmath>

namespace draw_canvas {
    class PatternTool final : public ToolBase {
    public:
        explicit PatternTool(float aspect_ratio = 2.0f) : aspect_ratio_(aspect_ratio) {}
        virtual ~PatternTool() = default;

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
                    // Calculate radius considering aspect ratio
                    float dx = canvas_x - center_x;
                    float dy = (canvas_y - center_y) * aspect_ratio_;
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
        float aspect_ratio_; // Terminal character aspect ratio (height:width)

        void drawCircle(Canvas& canvas, int cx, int cy, int radius) {
            // Use midpoint circle algorithm with aspect ratio correction
            int x = radius;
            int y = 0;
            int decision = 1 - radius;

            while (y <= x) {
                // Plot points in all octants, adjusting y for aspect ratio
                plotCirclePoints(canvas, cx, cy, x, static_cast<int>(y / aspect_ratio_));

                y++;
                if (decision <= 0) {
                    decision += 2 * y + 1;
                } else {
                    x--;
                    decision += 2 * (y - x) + 1;
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

#endif // PATTERN_TOOL_HPP