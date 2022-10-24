#pragma once

#include <SDL_image.h>
#include <string>
#include <vector>

#include <sys/stat.h>

#include <fstream>
#include <iostream>

#include <alut.h>
#include<al.h>

namespace RKGBin {

	struct soundInfo {

		char name[100];

		ALenum format;
		int64_t* data;
		ALsizei size;
		ALsizei freq;
		ALboolean loop;

		soundInfo() {

			strcpy_s(name, "");

			format = -1;
			data = nullptr;
			size = -1;
			freq = -1;
			loop = false;

		}

		soundInfo(std::string name_, ALenum format_, int64_t* data_, ALsizei size_, ALsizei freq_, ALboolean loop_) {

			strcpy_s(name, name_.c_str());

			format = format_;
			data = data_;
			size = size_;
			freq = freq_;
			loop = loop_;

		}

	};

	struct sound {

		std::string name;

		soundInfo info;

		ALuint buffer;

		sound() {

			name = "";

			info = soundInfo();

			buffer = -1;

		}

		sound(std::string name_, soundInfo info_, ALuint buffer_) {

			name = name_;

			info = info_;

			buffer = buffer_;

		}

	};

	struct image {

		SDL_Surface* surface;
		std::string name;

		image() {

			surface = nullptr;
			name = "";

		}

		image(SDL_Surface* image_, std::string name_) {

			surface = image_;
			name = name_;

		}

	};

	struct imageBinary {

		struct pixelFormat {

			struct sdlpallete {

				struct sdlcolors {

					Uint8 r = NULL;
					Uint8 g = NULL;
					Uint8 b = NULL;
					Uint8 a = NULL;

				};

				int ncolors = NULL;
				sdlcolors colors = sdlcolors();

			};

			bool hasFormat = false;

			Uint32 format = NULL;
			sdlpallete palette = sdlpallete();
			Uint8 BitsPerPixel = NULL;
			Uint8 BytesPerPixel = NULL;

			Uint32 Rmask = NULL;
			Uint32 Gmask = NULL;
			Uint32 Bmask = NULL;
			Uint32 Amask = NULL;

			int refcount = NULL;

			pixelFormat(SDL_Surface* surface = nullptr) {

				if (surface == nullptr) {

					return;

				}

				SDL_PixelFormat* sformat = surface->format;

				format = sformat->format;

				if (sformat->palette != NULL) {

					hasFormat = true;

					palette.ncolors = sformat->palette->ncolors;

					palette.colors.r = sformat->palette->colors->r;
					palette.colors.g = sformat->palette->colors->g;
					palette.colors.b = sformat->palette->colors->b;
					palette.colors.a = sformat->palette->colors->a;

				}

				else {

					palette.ncolors = NULL;

					palette.colors.r = NULL;
					palette.colors.g = NULL;
					palette.colors.b = NULL;
					palette.colors.a = NULL;

				}

				BitsPerPixel = sformat->BitsPerPixel;
				BytesPerPixel = sformat->BytesPerPixel;
				Rmask = sformat->Rmask;
				Gmask = sformat->Gmask;
				Bmask = sformat->Bmask;
				Amask = sformat->Amask;

				refcount = sformat->refcount;

			}

		};

		char name[100];

		pixelFormat format;
		int w;
		int h;
		int pitch;

		imageBinary() {

			strcpy_s(name, "");

			format = pixelFormat();
			w = 0;
			h = 0;
			pitch = 0;

		}

		imageBinary(SDL_Surface* surface, std::string name_) {

			strcpy_s(name, name_.c_str());

			format = pixelFormat(surface);
			w = surface->w;
			h = surface->h;
			pitch = surface->pitch;

		}

	};

	struct file {

		char fileName[100];
		int imageAmount = 0;
		int soundAmount = 0;

		file() {

			strcpy_s(fileName, "");

		}

		file(std::string fileName_) {

			strcpy_s(fileName, fileName_.c_str());

		}

	};

	class RKGBinary
	{

	public:

		static void createFile(std::string fileName, std::vector<RKGBin::image> images, std::vector<RKGBin::sound> sounds);
		//static void createFileTest(std::string fileName, std::vector<image> images, std::vector<sound> sounds);

		static file readHeader(std::string filePath, FILE** filePointer);
		static void readAssets(file header, FILE* filePointer, std::vector<image>* images, std::vector<sound>* sounds);
		static void readFile(std::string filePath, std::vector<image>* images, std::vector<sound>* sounds);

	private:

		static Uint32 getpixel(SDL_Surface* surface, int i, int bpp);

		static void putpixel(SDL_Surface* surface, int i, int bpp, Uint32 pixel);

		static SDL_Surface* createSurface(imageBinary img);

	};

}

extern std::string EXECUTABLE_LOCATION;
extern std::vector<RKGBin::image> IMAGE_ASSETS;
extern std::vector<RKGBin::sound> SOUND_ASSETS;