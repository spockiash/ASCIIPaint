#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <array>
namespace constants {
    constexpr std::array<char, 26> CapitalLetters = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    constexpr std::array<char, 26> LowercaseLetters = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };
    constexpr std::array<char, 10> Numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    // Array of special printable ASCII characters
    constexpr std::array<char, 31> SpecialCharacters = {
        '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
        ':', ';', '<', '=', '>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~'
    };
}

#endif // CONSTANTS_HPP
