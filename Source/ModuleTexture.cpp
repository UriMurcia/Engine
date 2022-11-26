#include "ModuleTexture.h"

ModuleTexture::ModuleTexture()
{}

ModuleTexture::~ModuleTexture()
{
}

void ModuleTexture::FillImageFormat() {
	switch (md.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internalFormat = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		assert(false && "Unsupported format");
	}
}

GLuint ModuleTexture::LoadTexture(std::string fileDir) {
	HRESULT result = E_FAIL;
	DirectX::ScratchImage img;
	DirectX::ScratchImage image;

	std::wstring filename = std::wstring(fileDir.begin(), fileDir.end());

	result = LoadFromDDSFile(filename.c_str(), DirectX::DDS_FLAGS_NONE, &md, img);
	if (FAILED(result)) {
		result = LoadFromTGAFile(filename.c_str(), &md, img);
		if (FAILED(result)) {
			result = LoadFromWICFile(filename.c_str(), DirectX::WIC_FLAGS_NONE, &md, img);
			if (FAILED(result)) {
				LOG_ENGINE("Material convertor error: texture loading failed (%s)", fileDir.c_str());
			}
		}
	}

	DirectX::FlipRotate(img.GetImages(), 1, img.GetMetadata(), DirectX::TEX_FR_FLIP_VERTICAL, image);
	
	//textLoaded = moduleTexture->LoadTexture("Images/test.png");
	GLuint texture;

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FillImageFormat();

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, md.width, md.height, 0, format, type, image.GetPixels());

	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}