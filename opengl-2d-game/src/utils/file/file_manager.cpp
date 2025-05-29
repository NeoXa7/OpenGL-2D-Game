#include <pch.h>
#include "file_manager.h"
#include <utils/logger.h>

namespace FileManager {
	std::string ReadFile(const char* file_path) {
		std::ifstream file_to_read(file_path);
		if (!file_to_read.is_open()) {
			LOGGER::Error("Failed to open file [Path : ", file_path, "]");
			return {};
		}

		std::stringstream buffer;
		buffer << file_to_read.rdbuf();
		return buffer.str();  // OK! The string is returned by value
	}
}