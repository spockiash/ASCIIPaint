#include "draw_canvas.hpp"
/*********************************************
 *               Canvas.hpp                  *
 *                                           *
 * Author: Bobo                              *
 * Date:   23.10.2024                        *
 * Description: Custom library for drawing   *
 * with ASCII characters.                    *
 *                                           *
 *********************************************/
namespace draw_canvas {

Canvas::Canvas(int width, int height)
    : width(width), height(height) {
    matrix.resize(height, std::vector<char>(width, ' '));
}

void Canvas::setChar(int x, int y, char c) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        matrix[y][x] = c;
    }
}

void Canvas::getChar(int x, int y, char c) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        matrix[y][x] = c;
    }
}

std::vector<std::string> Canvas::getPrintable()
{
    std::vector<std::string> output;
    for(int y = 0; y < height; y++)
    {
        std::string line;
        for(int x = 0; x < width; x++)
        {
            char c = matrix[y][x];
            line.push_back(c);
        }
        output.push_back(line);
    }
    return output;
}

}
