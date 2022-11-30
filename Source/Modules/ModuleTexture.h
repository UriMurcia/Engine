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

	GLuint LoadTexture(std::string fileDir, const char* fullTexturePath);

	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	int format;
	int internalFormat;
	int type; 
	std::wstring filename;

private:
	void FillImageFormat();
	bool LoadImageFromPath(std::string fileDir, std::string typeOfError);

};

