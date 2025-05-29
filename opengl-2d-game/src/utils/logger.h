#pragma once
#include <cstdint>
#include <string>
#include "console/console.h"

enum LOGGER_CODES : int {
	L_ERROR = 404,
	L_WARNING,
	L_MESSAGE
};

namespace LOGGER {
	template <typename... Args>
	int Error(const char* error_from, const Args&... args) {
		static std::string result;
		std::ostringstream oss;
		(oss << ... << args);
		result = oss.str();

		Console::SetConsoleTextColor(CONSOLE_RED);
		std::cout << "[ERROR]" << " [" << error_from << "] " << result << '\n';

		return L_ERROR;
	}

	template <typename... Args>
	int Information(const char* info_from, const Args&... args) {
		static std::string result;
		std::ostringstream oss;
		(oss << ... << args);
		result = oss.str();

		Console::SetConsoleTextColor(CONSOLE_YELLOW);
		std::cout << "[INFO]" << " [" << info_from << "] " << result << '\n';
		return L_MESSAGE;
	}
}