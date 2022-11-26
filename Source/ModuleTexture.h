#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew.h"
#include "DirectXTex.h"

#include <string>

class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	GLuint LoadTexture(std::string fileDir);
	void FillImageFormat();

	DirectX::TexMetadata md;
	int format;
	int internalFormat;
	int type;


};

