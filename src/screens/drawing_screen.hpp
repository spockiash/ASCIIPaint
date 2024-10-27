#ifndef DRAWING_SCREEN_HPP
#define DRAWING_SCREEN_HPP


#include "../constants.hpp"
#include "../draw_canvas/characters.hpp"
#include "screen_base.hpp"
#include "../draw_canvas/draw_canvas.hpp"
#include <memory>

using namespace ftxui;
using namespace draw_canvas;

namespace screens {
class DrawingScreen : public screens::ScreenBase {
public:
    DrawingScreen(int width, int height) : canvas(width, height) {
        InitializeComponents();
    }

    void ResizeCanvas(int width, int height) {
        // Implementation here
    }

    Component Render() override {
        auto matrixContent = canvas.getPrintable();
        auto canvasElements = CanvasToElements(matrixContent);
        auto buttonElements = RenderCharButtons();
        auto canvas_display = vbox(canvasElements) | border;
        return Renderer(charButtonsContainer,[&, canvas_display, buttonElements, this] {
            return vbox({
                text(constants::programNameAndVersion) | bold | center,
                hbox(text("F1 - File"),
                     separator(),
                     text("F2 - Canvas"),
                     separator(),
                     text("F3 - Tools"),
                     separator(),
                     text("Selected: "),
                     text(std::string(1,selected_char)) | color(Color::White) | bold,
                     separator(),
                     text("Tool size: "),
                     text(std::to_string(tool_size)) | color(Color::White) | bold,
                     toolDecreaseBtn->Render(),
                     toolIncreaseBtn->Render(),
                     separator()
                    ) | flex ,
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

            // Start drawing on mouse press
            if (mouse.button == ftxui::Mouse::Left && mouse.motion == Mouse::Pressed) {
                is_drawing = true;
            }
            // Stop drawing on release
            else if (mouse.button == Mouse::Left && mouse.motion == Mouse::Released) {
                is_drawing = false;
            }

            // Only apply drawing if the mouse is moving while the left button is pressed, or
            // if the left button is pressed again (initial drawing point)
            if (is_drawing && (mouse.motion == Mouse::Moved || mouse.motion == Mouse::Pressed)) {
                // Adjust these offsets based on your UI layout
                const int HEADER_OFFSET = 1;    // Title
                const int TOOL_OFFSET = 0;      // Tool selector
                const int BORDER_OFFSET = 1;    // Border

                int canvas_x = mouse.x - BORDER_OFFSET;
                int canvas_y = mouse.y - (HEADER_OFFSET + TOOL_OFFSET + BORDER_OFFSET);

                // Ensure drawing only happens within the canvas bounds
                if (canvas_x >= 0 && canvas_x < canvas.getWidth() &&
                    canvas_y >= 0 && canvas_y < canvas.getHeight()) {
                    // Set the character at the current mouse position
                    canvas.setChar(canvas_x, canvas_y, selected_char);

                    // Ask FTXUI to redraw the canvas
                    return true;  // Consume the event, redraw
                }
            }
        }
        // Your other event handling logic here
        return false;
    }

private:
    char selected_char = 'a';
    bool is_drawing = false;
    int tool_size = 1;
    draw_canvas::Canvas canvas;

    std::vector<Component> toolbarButtons;
    Component toolIncreaseBtn;
    Component toolDecreaseBtn;

    draw_canvas::Characters chars;
    std::vector<char> char_set;
    std::vector<Component> characterButtons;
    Component charButtonsContainer;  // Add this to manage the button

    enum SwitchDirections
    {
        FORWARD,
        BACKWARD
    };

    std::vector<Component> CreateToolbarButtons()
    {
        auto fileButton = Button("File", []{ auto x =1 ;});
        toolbarButtons.push_back(fileButton);

    }

    void InitializeToolbarButtons()
    {
        toolIncreaseBtn = Button("+", [this]{
            tool_size++;
        });
        toolDecreaseBtn = Button("-", [this]{
            if(tool_size > 1)
                tool_size--;
        });

        charButtonsContainer->Add(toolIncreaseBtn);
        charButtonsContainer->Add(toolDecreaseBtn);
    }



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

    void InitializeComponents()
    {
        chars = Characters();
        char_set = chars.getActiveCharacterSet();

        PopulateCharacterSelectionComponents();
        InitializeToolbarButtons();
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


    // Helper function to render a character button
    Element RenderCharButton(Component button, char label, Color bg_focus, Color bg_normal) {
        return button->Render() |
               color(Color::White) |
               bgcolor(button->Focused() ? bg_focus : bg_normal) |
               size(WIDTH, EQUAL, 3);
    }

    std::vector<Element> RenderCharButtons()
    {
        std::vector<Element> button_elements;
        for (size_t i = 0; i < characterButtons.size(); ++i) {
            button_elements.push_back(
                RenderCharButton(characterButtons[i], char_set[i], Color::Blue, Color::Black)
                );
        }
        return button_elements;
    }

    // Helper function to convert Canvas lines to FTXUI Elements
    ftxui::Elements CanvasToElements(const std::vector<std::string>& lines) {
        ftxui::Elements elements;
        for (const auto& line : lines) {
            elements.push_back(ftxui::text(line));
        }
        return elements;
    }

};


}

#endif // DRAWING_SCREEN_HPP
