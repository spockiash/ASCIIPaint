#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include <vector>
namespace draw_canvas {

    enum CharacterSetOptions {
        UPPER,
        LOWER,
        NUMS,
        SPECIAL
    };

    class Characters {
    private:
        // Selected option from CharacterSetOptions
        CharacterSetOptions selectedOption;

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

        std::vector<char> getUpperCase() { return upperCase; }
        std::vector<char> getLowerCase() { return lowercaseLetters; }
        std::vector<char> getNumbers() { return numbers; }
        std::vector<char> getSpecial() { return specialCharacters; }
    public:
        // Constructor that defaults the selected option
        Characters() : selectedOption(UPPER) {}
        // Set the selected option
        void SetSelectedOption(CharacterSetOptions option) {
            selectedOption = option;
        }
        // Get the character set based on the selected option
        std::vector<char> GetCharacterSet() {
            switch (selectedOption) {
            case UPPER:
                return getUpperCase();
            case LOWER:
                return getLowerCase();
            case NUMS:
                return getNumbers();
            case SPECIAL:
                return getSpecial();
            default:
                return getUpperCase(); // Return an upper case vector if no valid option is set
            }
        }
    };
}

#endif // CHARACTERS_HPP
