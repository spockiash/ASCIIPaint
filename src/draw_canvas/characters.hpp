#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include <algorithm>
#include <vector>
namespace draw_canvas {
    class Characters {
    public:
        Characters() : activeCharacterSet(&characterSets[0]) {}

        enum SwitchDirections
        {
            FORWARD,
            BACKWARD
        };

        const std::vector<char>& getActiveCharacterSet() const { return *activeCharacterSet; }

        void SwitchCharacterSet(SwitchDirections direction) {
            size_t index = activeIndex();

            if (direction == FORWARD) {
                index = (index + 1) % characterSets.size();
            } else { // BACKWARD
                index = (index == 0) ? characterSets.size() - 1 : index - 1;
            }

            activeCharacterSet = &characterSets[index];
        }
    private:
        std::vector<char> upperCase = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
        };
        std::vector<char> lowercaseLetters = {
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
        };
        std::vector<char> numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        // Array of special printable ASCII characters
        std::vector<char> specialCharacters = {
            '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
            ':', ';', '<', '=', '>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~'
        };

        std::vector<std::vector<char>> characterSets = { upperCase, lowercaseLetters, numbers, specialCharacters };

        const std::vector<char>* activeCharacterSet;

        // Helper to get the current index of the active character set
        size_t activeIndex() const {
            auto it = std::find(characterSets.begin(), characterSets.end(), *activeCharacterSet); //find the index of element inside dataset
            return std::distance(characterSets.begin(), it);
        }
    };
}

#endif // CHARACTERS_HPP
