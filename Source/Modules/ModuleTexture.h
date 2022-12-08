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

	GLuint LoadTexture(const std::string& fileDir, const char* fullTexturePath);

private:
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	int format = 0;
	int internalFormat = 0;
	int type = 0;
	std::wstring filename;

	void FillImageFormat();
	bool LoadImageFromPath(std::string fileDir);

};

