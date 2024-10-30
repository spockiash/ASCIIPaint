#ifndef DRAWING_SCREEN_HPP
#define DRAWING_SCREEN_HPP


#include "../constants.hpp"
#include "../draw_canvas/characters.hpp"
#include "screen_base.hpp"
#include "../draw_canvas/draw_canvas.hpp"
#include "screen_helper.hpp"
#include "../draw_canvas/pencil_tool.hpp"
#include "../draw_canvas/eraser_tool.hpp"
#include "../draw_canvas/circle_tool.hpp"
#include "../draw_canvas/pattern_tool.hpp"
#include "../program_state.hpp"
#include <memory>

#include "../draw_canvas/line_tool.hpp"

using namespace ftxui;
using namespace draw_canvas;
using namespace program_state;

namespace screens {
class DrawingScreen : public screens::ScreenBase {
public:
    DrawingScreen(int width, int height, program_state::ProgramStatePtr program_state) : ScreenBase(std::move(program_state)), canvas(width, height) {
        InitializeTool();
        InitializeComponents();
    }

    void ResizeCanvas(int width, int height) {
        // Implementation here
    }

    Component Render() override {
        auto matrixContent = canvas.GetPrintable();
        auto canvasElements = ScreenHelper::CanvasToElements(matrixContent);
        auto buttonElements = ScreenHelper::RenderButtons(characterButtons);
        auto canvas_display = vbox(canvasElements) | border;
        auto toolbar = ScreenHelper::GetToolbar();

        return Renderer(charButtonsContainer,[&, canvas_display, buttonElements, toolbar, this] {
            return vbox({
                text(constants::programNameAndVersion) | bold | center,
                toolbar,
                vbox(canvas_display) | flex,
                hbox({buttonElements}) | border | center,
            });
        });
    }

    bool HandleEvent(ftxui::Event event) override {
        // Let the container handle events first
        if (charButtonsContainer->OnEvent(event)) {
            return true;
        }
        // Handle mouse and key events for drawing
        if (event.is_mouse()) {
            auto mouse = event.mouse();
            return statePtr->current_tool->HandleEvent(mouse, canvas);
        }
        // Your other event handling logic here
        return false;
    }

private:
    char selected_char = 'a';
    bool is_drawing = false;
    int tool_size = 1;
    draw_canvas::Canvas canvas;

    Component toolbarContainer;
    Component fileMenuBtn;
    Component toolSizeSlider;

    int selectedToolIndex = 0;
    std::vector<Component> toolbarComponents;
    Component toolIncreaseBtn;
    Component toolDecreaseBtn;
    bool showFileMenu = false;

    draw_canvas::Characters chars;
    std::vector<char> char_set;
    std::vector<Component> characterButtons;
    Component charButtonsContainer;  // Add this to manage the button

    draw_canvas::PencilTool tool = PencilTool();

    //std::unique_ptr<ToolBase> current_tool;
    //std::unordered_map<std::string, std::function<std::unique_ptr<ToolBase>()>> tools;

    enum SwitchDirections
    {
        FORWARD,
        BACKWARD
    };

    Component AddPrevButton()
    {
        return Button("<<", [this]{
            chars.SwitchCharacterSet(Characters::BACKWARD);
            char_set = chars.getActiveCharacterSet();
            PopulateCharacterSelectionComponents();
        });
    }

    Component AddNextButton()
    {
        return Button(">>", [this]{
            chars.SwitchCharacterSet(Characters::FORWARD);
            char_set = chars.getActiveCharacterSet();
            PopulateCharacterSelectionComponents();
        });
    }

    void InitializeTool()
    {
        // Initialize with default tool
        statePtr->current_tool = std::make_unique<PencilTool>();
        //Add tools to unordered map
        statePtr->tools[constants::pencilToolLabel] = []() { return std::make_unique<PencilTool>(); };
        statePtr->tools[constants::eraserToolLabel] = []() { return std::make_unique<EraserTool>(); };
        statePtr->tools[constants::lineToolLabel] = []() { return std::make_unique<LineTool>(); };
        statePtr->tools[constants::circleToolLabel] = []() { return std::make_unique<CircleTool>(); };
        statePtr->tools[constants::patternToolLabel] = []() { return std::make_unique<PatternTool>(); };

        tool = PencilTool();
    }

    void InitializeComponents()
    {
        chars = Characters();
        char_set = chars.getActiveCharacterSet();
        PopulateCharacterSelectionComponents();
    }

    void PopulateCharacterSelectionComponents()
    {
        characterButtons.clear();
        characterButtons.push_back(AddPrevButton());
        for(const char i : char_set)
        {
            auto c = i;
            auto button = Button(std::string(1, i), [c, this] {
                selected_char = c;
                statePtr->current_tool->SetCharacter(c);
            });
            characterButtons.push_back(button);
        }
        characterButtons.push_back(AddNextButton());
        charButtonsContainer = Container::Horizontal({characterButtons});
    }
};
}

#endif // DRAWING_SCREEN_HPP
