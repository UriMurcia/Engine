#pragma once
#include "Globals.h"
#include "Application.h"

#include <vector>

class EditorConfiguration
{
public:
	EditorConfiguration();

	void ShowConfigurationWindow();

private:
	std::vector<float> fpsLog;
};
