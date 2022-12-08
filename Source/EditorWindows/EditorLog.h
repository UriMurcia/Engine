#pragma once
#include "Globals.h"
#include "Application.h"

#include <vector>
#include <string>

class EditorLog
{
public:
	EditorLog();

	void ShowLogWindow();
	void AddTextToLog(char* const text);

	std::vector<std::string> textsLog;
};

