#include "paint_tools.hpp"
#include <vector>

std::vector<char> GetAsciiCharacterSet()
{
    std::vector<char> asciiSet;
    // Printable ASCII characters range from 32 (space) to 126 (~)
    for (char c = 32; c <= 126; ++c) {
        asciiSet.push_back(c);
    }

    return asciiSet;
}
