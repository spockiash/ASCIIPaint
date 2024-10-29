#ifndef PENCIL_TOOL_HPP
#define PENCIL_TOOL_HPP

#include "tool_base.hpp"
#include "../constants.hpp"
using namespace ftxui;
namespace draw_canvas {
class PencilTool final : public ToolBase
{
public:
    virtual ~PencilTool() = default;

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

            if (canvas_x >= 0 && canvas_x < canvas.getWidth() &&
                canvas_y >= 0 && canvas_y < canvas.getHeight()) {
                canvas.setChar(canvas_x, canvas_y, selected_char);
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] const char* GetName() const override { return constants::pencilToolLabel; }

    void SetCharacter(char selected_char) override
    {
        this->selected_char = selected_char;
    }
};
}

#endif // PENCIL_TOOL_HPP
