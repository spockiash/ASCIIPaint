#ifndef DRAW_CANVAS_HPP
#define DRAW_CANVAS_HPP

/*********************************************
 *               Canvas.hpp                  *
 *                                           *
 * Author: Bobo                              *
 * Date:   23.10.2024                        *
 *                                           *
 *********************************************/

#include <string>
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
        int getWidth();
        int getHeight();
        void resize(int width, int height);

        std::vector<std::string> getPrintable();
    };
}


#endif // DRAW_CANVAS_HPP
