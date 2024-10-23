#ifndef DRAW_CANVAS_HPP
#define DRAW_CANVAS_HPP

#include <vector>
namespace draw_canvas {
    class Canvas {
    private:
        std::vector<std::vector<char>> matrix;
        int width, height;
    public:
        Canvas(int width, int height);

        void setChar(int x, int y, char c);
        void getChar(int y, int x, char c);
    };
}


#endif // DRAW_CANVAS_HPP
