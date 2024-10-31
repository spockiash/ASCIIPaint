#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace constants {
    //TOOL OFFSETS
    constexpr int BORDER_OFFSET = 1;
    constexpr int HEADER_OFFSET = 1;
    constexpr int TOOL_OFFSET = 1;
    //CANVAS UI OFFSETS
    constexpr int CANVAS_X_MARGIN = 2;
    constexpr int CANVAS_Y_MARGIN = 9;

    constexpr const char* programNameAndVersion = "ASCII Painter v 0.2.0";
    constexpr const char* fileOptionLabel = "F1-FILE\t";
    constexpr const char* toolsOptionLabel = "F2-TOOLS\t";
    constexpr const char* canvasOptionLabel = "F3-CANVAS\t";
    constexpr const char* saveOptionLabel = "F5-SAVE\t";
    constexpr const char* loadOptionLabel = "F8-LOAD\t";
    constexpr const char* exitOptionLabel = "F12-EXIT\t";

    constexpr const char* pencilToolLabel = "Pencil";
    constexpr const char* eraserToolLabel = "Eraser";
    constexpr const char* lineToolLabel = "Line";
    constexpr const char* circleToolLabel = "Circle";
    constexpr const char* patternToolLabel = "Pattern";

    constexpr const char* fileSaveLabel = "Save";
    constexpr const char* loadSaveLabel = "Load";
    constexpr const char* exitLabel = "Exit";
}

#endif // CONSTANTS_HPP
