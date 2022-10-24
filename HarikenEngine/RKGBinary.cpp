#include "RKGBinary.h"
#include "stdafx.h"
#include <io.h>

std::string EXECUTABLE_LOCATION = "";
std::vector<RKGBin::image> IMAGE_ASSETS;
std::vector<RKGBin::sound> SOUND_ASSETS;

using namespace RKGBin;

void RKGBin::RKGBinary::createFile(std::string fileName, std::vector<RKGBin::image> images, std::vector<RKGBin::sound> sounds)
{

	file temp(fileName);
	temp.imageAmount = images.size();
	temp.soundAmount = sounds.size();

	FILE* fptr;

	std::string filePath = EXECUTABLE_LOCATION + "Output/" + fileName + ".rkg";

	if (errno_t error = fopen_s(&fptr, filePath.c_str(), "wb") != 0) {
		std::cout << "fopen error: " << error << std::endl;
		std::cout << "Could not create " << filePath << std::endl;
		return;
	}

	else
		fwrite(&temp, sizeof(file), 1, fptr);

	for (size_t i = 0; i < images.size(); i++) {

		SDL_Surface* surface = images[i].surface;
		imageBinary tempImage = imageBinary(images[i].surface, images[i].name);

		fwrite(&tempImage, sizeof(imageBinary), 1, fptr);

		for (int i = 0; i < tempImage.h * tempImage.w; i++) {

			Uint32 p = getpixel(surface, i, surface->format->BytesPerPixel);
			fwrite(&p, sizeof(Uint32), 1, fptr);

		}

	}

	for (size_t i = 0; i < sounds.size(); i++) {

		soundInfo tempInfo = sounds[i].info;

		fwrite(&tempInfo, sizeof(soundInfo), 1, fptr);

		for (int i = 0; i < tempInfo.size / 8; i++) {

			int64_t data = tempInfo.data[i];
			fwrite(&data, sizeof(int64_t), 1, fptr);

		}

		alDeleteBuffers(1, &sounds[i].buffer);

	}

	std::cout << "File created successfully" << std::endl;

}
/* Test function
void RKGBin::RKGBinary::createFileTest(std::string fileName, std::vector<RKGBin::image> images, std::vector<RKGBin::sound> sounds)
{

	file temp(fileName);
	temp.imageAmount = images.size();
	temp.soundAmount = sounds.size();
	
	FILE* fptr;

	std::string filePath = EXECUTABLE_LOCATION + "Output/" + fileName + ".rkg";

	if (errno_t error = fopen_s(&fptr, filePath.c_str(), "wb") != 0) {
		std::cout << "fopen error: " << error << std::endl;
		std::cout << "Could not create " << filePath << std::endl;
		return;
	}
	
	else
		fwrite(&temp, sizeof(file), 1, fptr);
	
	for (size_t i = 0; i < images.size(); i++) {

		SDL_Surface* surface = images[i].surface;
		imageBinary tempImage = imageBinary(images[i].surface, images[i].name);

		fwrite(&tempImage, sizeof(imageBinary), 1, fptr);

		for (int i = 0; i < tempImage.h * tempImage.w; i++) {

			Uint32 p = getpixel(surface, i, surface->format->BytesPerPixel);
			fwrite(&p, sizeof(Uint32), 1, fptr);

		}

	}

	for (size_t i = 0; i < sounds.size(); i++) {

		soundInfo tempInfo = sounds[i].info;

		fwrite(&tempInfo, sizeof(soundInfo), 1, fptr);

		for (int i = 0; i < tempInfo.size / 8; i++) {

			int64_t data = tempInfo.data[i];
			fwrite(&data, sizeof(int64_t), 1, fptr);

		}

		alDeleteBuffers(1, &sounds[i].buffer);

	}

	fclose(fptr);
	 
	std::cout << "File created successfully" << std::endl;

}
*/

file RKGBin::RKGBinary::readHeader(std::string filePath, FILE** filePointer)
{

	FILE* fptr = *filePointer;

	std::string path;

	for (size_t i = 0; i < filePath.size(); i++) {

		if (filePath[i] != '"')
			path += filePath[i];

	}

	if (path == "") {

		std::cout << "File cannot be opened" << std::endl;
		return file();

	}

	file header;

	try {

		fopen_s(&fptr, path.c_str(), "rb");

	}

	catch (errno_t error) {

		std::cout << "File cannot be opened" << std::endl;
		return file();

	}

	fread(&header, sizeof(file), 1, fptr);

	*filePointer = fptr;

	return header;

}

void RKGBin::RKGBinary::readAssets(file header, FILE* filePointer, std::vector<image>* images, std::vector<sound>* sounds)
{

	FILE* fptr = filePointer;

	fpos_t pos = ftell(fptr);

	imageBinary tempImg;

	for (int i = 0; i < header.imageAmount; i++) {

		fread(&tempImg, sizeof(imageBinary), 1, fptr);

		imageBinary img = imageBinary(SDL_CreateRGBSurface(0, tempImg.w, tempImg.h, tempImg.format.BitsPerPixel, tempImg.format.Rmask, tempImg.format.Gmask, tempImg.format.Bmask, tempImg.format.Amask), tempImg.name);

		SDL_Surface* surface = createSurface(img);

		SDL_UnlockSurface(surface);

		for (int i = 0; i < tempImg.h * tempImg.w; i++) {

			Uint32 p;
			fread(&p, sizeof(Uint32), 1, fptr);

			putpixel(surface, i, img.format.BytesPerPixel, p);

		}

		SDL_LockSurface(surface);

		if (images != nullptr)
			images->push_back(image(surface, img.name));

	}

	soundInfo tempSnd;

	for (int i = 0; i < header.soundAmount; i++) {

		fread(&tempSnd, sizeof(soundInfo), 1, fptr);

		int64_t* data = (int64_t*)malloc(tempSnd.size);

		for (int j = 0; j < tempSnd.size / 8; j++) {

			fread(&data[j], sizeof(int64_t), 1, fptr);

		}

		soundInfo info = soundInfo(tempSnd.name, tempSnd.format, data, tempSnd.size, tempSnd.freq, tempSnd.loop);

		ALuint sndBuffer;

		alGenBuffers(1, &sndBuffer);

		alBufferData(sndBuffer, tempSnd.format, data, tempSnd.size, tempSnd.freq);

		if (sounds != nullptr)
			sounds->push_back(sound(info.name, info, sndBuffer));

	}

	fsetpos(fptr, &pos);

}

void RKGBin::RKGBinary::readFile(std::string filePath, std::vector<RKGBin::image>* images, std::vector<RKGBin::sound>* sounds)
{

	FILE* fptr;

	file header = readHeader(filePath, &fptr);
	
	readAssets(header, fptr, images, sounds);
	
}

Uint32 RKGBin::RKGBinary::getpixel(SDL_Surface* surface, int i, int bpp)
{

	Uint8* p = (Uint8*)surface->pixels + i * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16*)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32*)p;
		break;

	default:
		return 0;
	}

}

void RKGBin::RKGBinary::putpixel(SDL_Surface* surface, int i, int bpp, Uint32 pixel)
{

	Uint8* p = (Uint8*)surface->pixels + i * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16*)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32*)p = pixel;
		break;
	}

}

SDL_Surface* RKGBin::RKGBinary::createSurface(imageBinary img)
{

	SDL_Surface* surface = SDL_CreateRGBSurface(0, img.w, img.h, img.format.BitsPerPixel, img.format.Rmask, img.format.Gmask, img.format.Bmask, img.format.Amask);

	surface->pitch = img.pitch;

	return surface;

}

