#pragma once
#include "Module.h"
#include "Globals.h"
#include "DirectXTex.h"
#include "glew.h"

#include <string>

class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	update_status Update();
	DirectX::ScratchImage LoadTexture(std::string path);
	GLuint texture;

};

