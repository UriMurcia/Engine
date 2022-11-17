#include "ModuleTexture.h"
#include "DirectXTex.h"

ModuleTexture::ModuleTexture()
{}

ModuleTexture::~ModuleTexture()
{
	glDeleteTextures(1, &texture);
}

bool ModuleTexture::Init() {
	LoadTexture("Images/Test-image-Baboon.ppm");

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FillImageFormat();

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, md.width, md.height, 0, format, type, img.GetPixels());
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, md.width, md.height, 0, GL_BGR, GL_UNSIGNED_BYTE, img.GetPixels());//change &texture probably

	glEnable(GL_TEXTURE_2D);
	return true;
}

update_status ModuleTexture::PreUpdate()
{

	return UPDATE_CONTINUE;
}

update_status ModuleTexture::Update() {

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 4 * 3));

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture);
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate()
{

	
	return UPDATE_CONTINUE;
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

void ModuleTexture::LoadTexture(std::string fileDir) {
	HRESULT result = E_FAIL;

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
}