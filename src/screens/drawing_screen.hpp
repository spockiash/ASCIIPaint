#ifndef DRAWING_SCREEN_HPP
#define DRAWING_SCREEN_HPP


#include "../constants.hpp"
#include "../draw_canvas/characters.hpp"
#include "screen_base.hpp"
#include "../draw_canvas/draw_canvas.hpp"
#include "screen_helper.hpp"
#include "../draw_canvas/pencil_tool.hpp"
#include <memory>

using namespace ftxui;
using namespace draw_canvas;

namespace screens {
class DrawingScreen : public screens::ScreenBase {
public:
    DrawingScreen(int width, int height) : canvas(width, height) {
        InitializeTool();
        InitializeComponents();
    }

    void ResizeCanvas(int width, int height) {
        // Implementation here
    }

    Component Render() override {
        auto matrixContent = canvas.getPrintable();
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
            return tool.HandleEvent(mouse, canvas, selected_char);
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

    std::string currentTool = "Brush";
    std::vector<std::string> tools = {"Brush", "Eraser", "Fill"};
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

    void InitializeToolbar()
    {
        fileMenuBtn = Button("File", [this] {
            showFileMenu = true;
            // Callback will be implemented later
        });

        // Create tool selector
        auto toolSelector = Menu(&tools, &selectedToolIndex);

        toolSizeSlider = Slider("",&tool_size, 1, 10, 1);
        auto toolbar_elements = Container::Horizontal({
            fileMenuBtn,
            Renderer([](bool) { return text(" | "); }),  // Separator
            toolSelector | center,
            Renderer([](bool) { return text(" | "); }),  // Separator
            Container::Horizontal({
                Renderer([](bool) { return text("Size: "); }),
                toolSizeSlider
            })
        });
        toolbarContainer = toolbar_elements;
    }

    void InitializeTool()
    {
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
        for(size_t i = 0; i < char_set.size(); i++ )
        {
            auto c = char_set[i];
            auto button = Button(std::string(1, char_set[i]), [c, this] {
                selected_char = c;
            });
            characterButtons.push_back(button);
        }
        characterButtons.push_back(AddNextButton());
        charButtonsContainer = Container::Horizontal({characterButtons});
    }
};
}

#endif // DRAWING_SCREEN_HPP
