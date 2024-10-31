#ifndef PROGRAM_STATE_HPP
#define PROGRAM_STATE_HPP

#include "draw_canvas/tool_base.hpp"
#include <string>
#include <memory>
#include <functional>
using namespace draw_canvas;
namespace program_state{
struct ProgramState {
    std::unique_ptr<ToolBase> current_tool;
    std::unordered_map<std::string, std::function<std::unique_ptr<ToolBase>()>> tools;
    std::shared_ptr<Canvas> canvas;
};

using ProgramStatePtr = std::shared_ptr<ProgramState>;
}
#endif // PROGRAM_STATE_HPP
