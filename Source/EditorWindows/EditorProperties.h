#pragma once
#include "Globals.h"
#include "Application.h"
#include "Model.h"


class EditorProperties
{
public:
	EditorProperties();
	~EditorProperties();

	void ShowPropertiesWindow();
	void SetPropertiesWindow(Model&& model3D);

private:
	Model* model3Dselected = new Model();
};
