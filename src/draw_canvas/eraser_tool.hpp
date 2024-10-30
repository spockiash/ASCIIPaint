#ifndef ERASER_TOOL_H
#define ERASER_TOOL_H

#include "tool_base.hpp"
#include "../constants.hpp"
using namespace ftxui;
namespace draw_canvas {
class EraserTool final : public ToolBase
{
public:
    virtual ~EraserTool() = default;

    bool HandleEvent(const ftxui::Mouse& mouse, Canvas& canvas) override {
        // Start drawing on mouse press
        if (mouse.button == ftxui::Mouse::Left && mouse.motion == ftxui::Mouse::Pressed) {
            is_drawing = true;
        }
        // Stop drawing on release
        else if (mouse.button == ftxui::Mouse::Left && mouse.motion == ftxui::Mouse::Released) {
            is_drawing = false;
        }

        if (!is_drawing) return false;

        if (mouse.motion == ftxui::Mouse::Moved || mouse.motion == ftxui::Mouse::Pressed) {
            const int canvas_x = mouse.x - BORDER_OFFSET;
            const int canvas_y = mouse.y - (HEADER_OFFSET + TOOL_OFFSET + BORDER_OFFSET);

            if (canvas_x >= 0 && canvas_x < canvas.GetWidth() &&
                canvas_y >= 0 && canvas_y < canvas.GetHeight()) {
                canvas.SetChar(canvas_x, canvas_y, ' ');
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] const char* GetName() const override { return constants::eraserToolLabel; }
};
}

#endif // ERASER_TOOL_H
