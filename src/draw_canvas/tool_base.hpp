#ifndef TOOL_BASE_HPP
#define TOOL_BASE_HPP

#include "draw_canvas.hpp"
#include <ftxui/component/event.hpp>
namespace draw_canvas {
    class ToolBase {
    public:
        ToolBase(int header_offset = 1, int tool_offset = 0, int border_offset = 1)
            : HEADER_OFFSET(header_offset), TOOL_OFFSET(tool_offset), BORDER_OFFSET(border_offset) {}
        virtual bool HandleEvent(const ftxui::Mouse& mouse, Canvas& canvas) = 0;
        virtual const char* GetName() const = 0;
        virtual void SetCharacter(char selected_char)
        {
            this->selected_char = selected_char;
        };
    protected:
        char selected_char = 'A';
        bool is_drawing = false;
        int HEADER_OFFSET;
        int TOOL_OFFSET;
        int BORDER_OFFSET;
    };
}

#endif // TOOL_BASE_HPP
