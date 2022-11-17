#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew.h"

#include <string>

class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	update_status Update();
	update_status PreUpdate();
	update_status PostUpdate();
	void LoadTexture(std::string fileDir);
	void FillImageFormat();

	GLuint texture;
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	int format;
	int internalFormat;
	int type;


};

