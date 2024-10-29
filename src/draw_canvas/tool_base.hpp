#ifndef TOOL_BASE_HPP
#define TOOL_BASE_HPP

#include "draw_canvas.hpp"
#include <ftxui/component/event.hpp>
namespace draw_canvas {
    class ToolBase {
    public:
        virtual ~ToolBase() = default;
        virtual bool HandleEvent(const ftxui::Mouse& mouse, Canvas& canvas, int selected_char) = 0;
        virtual const char* GetName() const = 0;
    };
}

#endif // TOOL_BASE_HPP
