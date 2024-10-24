#ifndef TOOL_BASE_HPP
#define TOOL_BASE_HPP

#include "draw_canvas.hpp"
namespace draw_canvas {
    class ToolBase {
    public:
        virtual ~ToolBase() = default;
        virtual void SetSize(int size) { tool_size = size; }
        virtual int GetSize() { return tool_size; }
        virtual void ApplyTool(draw_canvas::Canvas& canvas, char symbol, int x, int y) = 0;
        virtual void ApplyTool(draw_canvas::Canvas& canvas, char symbol, int x0, int y0, int x1, int y1) = 0;

    protected:
        int tool_size = 1;

    };
}

#endif // TOOL_BASE_HPP
