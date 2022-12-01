#include "ModuleTexture.h"
#include "Shlwapi.h"

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

bool ModuleTexture::LoadImageFromPath(std::string fileDir) {
	filename = std::wstring(fileDir.begin(), fileDir.end());
	HRESULT result = E_FAIL;
	result = LoadFromDDSFile(filename.c_str(), DirectX::DDS_FLAGS_NONE, &md, img);
	if (FAILED(result)) {
		result = LoadFromTGAFile(filename.c_str(), &md, img);
		if (FAILED(result)) {
			result = LoadFromWICFile(filename.c_str(), DirectX::WIC_FLAGS_NONE, &md, img);
			if (FAILED(result)) {
				return false;
			}
		}
	}
	LOG_ENGINE("Image Found! (%s)", fileDir.c_str());
	return true;
}

GLuint ModuleTexture::LoadTexture(std::string fileDir, const char* fullTexturePath) {

	std::string path = "Textures/";

	bool textureLoaded = false;
	/*Checking texture in the path described inside the fbx directly*/
	LOG_ENGINE("Searching texture in path described by FBX...");
	textureLoaded = LoadImageFromPath(fileDir);

	if (!textureLoaded) {
		LOG_ENGINE("Checking same directory as FBX...");

		/*Checking texture in the same directory as the fbx (with the path of the image from inside the fbx)*/
		std::string stringFTP = fullTexturePath;
		size_t found = stringFTP.find_last_of("/\\");
		std::string textureDirectory = stringFTP.substr(0, found);
		textureLoaded = LoadImageFromPath(textureDirectory + "/" + fileDir);


		if (!textureLoaded) {
			LOG_ENGINE("Checking in /Textures folder...");
			
			/*Checking texture in the /Textures directory (with the path of the image from inside the fbx)*/
			textureLoaded = LoadImageFromPath(path + fileDir);


			if (!textureLoaded) {
				LOG_ENGINE("Checking if path described by FBX has extra '/'...");

				/*Checking texture in the same directory as the fbx (without the complete path of the image from inside the fbx, only the image name)*/
				std::string stringDir = fileDir;
				if (stringDir.find('/\\') != std::string::npos) {
					size_t foundTextureName = stringDir.find_last_of("/\\");
					std::string textureName = stringDir.substr(foundTextureName, stringDir.length());
					textureLoaded = LoadImageFromPath(textureDirectory + textureName);


					if (!textureLoaded) {
						LOG_ENGINE("...");

						/*Checking texture in the /Textures directory (without the complete path of the image from inside the fbx, only the image name)*/
						textureLoaded = LoadImageFromPath(path + textureName);


						if (!textureLoaded) {
							LOG_ENGINE("Material convertor error: texture loading failed (%s)", fileDir.c_str());
						}
					}
				}
			}
		}
	}

	DirectX::ScratchImage image;
	DirectX::FlipRotate(img.GetImages(), 1, img.GetMetadata(), DirectX::TEX_FR_FLIP_VERTICAL, image);
	

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