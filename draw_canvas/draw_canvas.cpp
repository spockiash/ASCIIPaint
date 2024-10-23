#include "draw_canvas.hpp"

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

}
