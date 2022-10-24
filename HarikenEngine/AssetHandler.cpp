#include "stdafx.h"
#include "AssetHandler.h"

using namespace HARIKEN;

std::unique_ptr<AssetHandler> AssetHandler::assetInstance = nullptr;

AssetHandler* HARIKEN::AssetHandler::GetInstance()
{
	if (assetInstance.get() == nullptr) {

		assetInstance.reset(new AssetHandler);
		assetInstance->loadCore();

	}

	return assetInstance.get();
}

void HARIKEN::AssetHandler::loadAssetList(HGLRC threadContext)
{

	WindowSys* winSys = WindowSys::GetInstance();
	wglMakeCurrent(winSys->getHDC(), threadContext);

	for (size_t i = 0; i < ASSET_LIST.size(); i++) {

		AssetFile* file = new AssetFile();

		file->header = RKGBin::RKGBinary::readHeader(ASSET_LIST[i], &file->filePointer);
		//file->loadAssets();
		assetFiles[file->getName()] = file;

	}

	wglMakeCurrent(NULL, NULL);

}

void HARIKEN::AssetHandler::loadCore()
{

	AssetFile* file = new AssetFile();

	file->header = RKGBin::RKGBinary::readHeader("CORE/CORE.RKG", &file->filePointer);

	file->keepLoaded();

	file->loadAssets();

	assetFiles[file->getName()] = file;

}

AssetFile* HARIKEN::AssetHandler::getAssetFile(std::string name)
{

	if (assetFiles.find(name) != assetFiles.end()) {
		assetFiles[name]->loadAssets();
		return assetFiles[name];
	}

	else
		return nullptr;

}

HARIKEN::AssetHandler::AssetHandler()
{

	alutInit(0, NULL);
	alGetError();

	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

}

HARIKEN::AssetHandler::~AssetHandler()
{

	for (std::map<std::string, AssetFile*>::iterator i = assetFiles.begin(); i != assetFiles.end(); i++) {

		for (std::map<std::string, ALuint*>::iterator j = i->second->sounds.begin(); j != i->second->sounds.end(); j++) {

			alDeleteBuffers(1, j->second);

		}

		for (std::map<std::string, Texture*>::iterator j = i->second->textures.begin(); j != i->second->textures.end(); j++) {

			glDeleteTextures(sizeof(GLuint), &j->second->textureID);

		}

	}

}