//
// Created by bobo on 31.10.24.
//

#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP
#include <fstream>
#include <string>
#include <vector>

class FileUtils {
public:
	// Save canvas data to a file
	static bool SaveToFile(const std::string& filename, const std::vector<std::string>& data) {
		std::ofstream file(filename);
		if (!file.is_open()) {
			return false;  // Failed to open the file
		}

		for (const auto& line : data) {
			file << line << '\n';  // Write each line of the canvas data to the file
		}

		file.close();
		return true;  // Successfully saved
	}

	// Load canvas data from a file
	static std::vector<std::string> LoadFromFile(const std::string& filename) {
		std::vector<std::string> data;
		std::ifstream file(filename);
		if (!file.is_open()) {
			return {};  // Return an empty vector if the file can't be opened
		}

		std::string line;
		while (std::getline(file, line)) {
			data.push_back(line);  // Read each line from the file into the vector
		}

		file.close();
		return data;  // Return the loaded data
	}
};

#endif //FILE_UTILS_HPP
