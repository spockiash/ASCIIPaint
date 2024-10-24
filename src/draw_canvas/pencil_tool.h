#ifndef PENCIL_TOOL_H
#define PENCIL_TOOL_H
#include "tool_base.hpp"
namespace draw_canvas {
    class PencilTool : public draw_canvas::ToolBase
    {
        void ApplyTool(draw_canvas::Canvas& canvas, char symbol, int x, int y) override {
            canvas.setChar(x,y, symbol); //Draw single character
        }
    };
}
#endif // PENCIL_TOOL_H
