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

int Canvas::getWidth() { return width; }
int Canvas::getHeight() { return height; }
void Canvas::resize(int new_width, int new_height)
{
    // First, resize the number of rows (height):
    if (new_height > height) {
    // If the new height is larger, add new rows filled with ' ' (spaces).
    for (int y = height; y < new_height; ++y) {
        matrix.push_back(std::vector<char>(new_width, ' '));
    }
    } else if (new_height < height) {
        // If the new height is smaller, truncate the rows.
        matrix.resize(new_height);
    }

    // Now, resize the number of columns (width) for each row:
    for (int y = 0; y < std::min(new_height, height); ++y) {
        if (new_width > width) {
            // If the new width is larger, add spaces to the end of each row.
            matrix[y].resize(new_width, ' ');
        } else if (new_width < width) {
            // If the new width is smaller, truncate the columns.
            matrix[y].resize(new_width);
        }
    }

    width = new_width;
    height = new_height;
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
