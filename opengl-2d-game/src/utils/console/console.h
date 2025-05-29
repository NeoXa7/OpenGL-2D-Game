#pragma once

#define CONSOLE_RED		FOREGROUND_RED | FOREGROUND_INTENSITY
#define CONSOLE_YELLOW	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define CONSOLE_WHITE	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

namespace Console
{
	void SetConsoleTextColor(WORD color);
	void CreateConsoleWindow(const char* title, int width = 1000, int height = 600);
	void DestroyConsoleWindow();
	void CreateLogNotification(const std::string& LogsName, const std::string& logFileName);
}