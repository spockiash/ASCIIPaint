#ifndef TOOL_BASE_HPP
#define TOOL_BASE_HPP

#include "draw_canvas.hpp"
#include <ftxui/component/event.hpp>

#include "../constants.hpp"

namespace draw_canvas {
    class ToolBase {
    public:
        virtual ~ToolBase() = default;

        virtual bool HandleEvent(const ftxui::Mouse& mouse, Canvas& canvas) = 0;
        [[nodiscard]] virtual const char* GetName() const = 0;
        virtual void SetCharacter(const char selected_char)
        {
            this->selected_char = selected_char;
        };
    protected:
        char selected_char = 'A';
        bool is_drawing = false;
        int HEADER_OFFSET = constants::HEADER_OFFSET;
        int TOOL_OFFSET = constants::TOOL_OFFSET;
        int BORDER_OFFSET = constants::BORDER_OFFSET;
    };
}

#endif // TOOL_BASE_HPP
