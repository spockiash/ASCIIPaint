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
#include <utility>
#include <vector>

namespace draw_canvas {
    using Matrix = std::vector<std::vector<char>>;
    class Canvas {
    private:
        std::vector<std::vector<char>> matrix;
        std::vector<std::vector<char>> snapshot;
        int width, height;
    public:
        Canvas(const int width, const int height) : width(width), height(height) {
            matrix.resize(height, std::vector<char>(width, ' '));
        }
        //Create snapshot of existing matrix before changing it
        void CreateSnapshot() {
            snapshot = matrix;
        }
        //Copy snapshot into main matrix to reset state after changint it
        void RevertSnapshot() {
            matrix = snapshot;
        }

        Matrix GetMatrix() {
            return matrix;
        }

        void SetChar(const int x, const int y, const char c) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                matrix[y][x] = c;
            }
        }

        void GetChar(const int x, const int y, const char c) {
            if (x >= 0 && x < width && y >= 0 && y < height) {
                matrix[y][x] = c;
            }
        }

        [[nodiscard]] int GetWidth() const { return width; }
        [[nodiscard]] int GetHeight() const { return height; }

        void Resize(const int new_width, const int new_height)
        {
            // First, resize the number of rows (height):
            if (new_height > height) {
                // If the new height is larger, add new rows filled with ' ' (spaces).
                for (int y = height; y < new_height; ++y) {
                    matrix.emplace_back(new_width, ' ');
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

        [[nodiscard]] std::vector<std::string> GetPrintable() const {
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
    };
}


#endif // DRAW_CANVAS_HPP
