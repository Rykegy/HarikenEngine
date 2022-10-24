/****************************************************************************
Singleton used to hold, read and distribute asset files that contain image textures and sounds.
****************************************************************************/

#pragma once

#include <al.h>
#include <alc.h>
#include <alut.h>
#include <glm.hpp>
#include <glew.h>
#include <map>
#include <Windows.h>

#include "ASSET_LIST.h"
#include "RKGBinary.h"

#include<SDL.h>

namespace HARIKEN {

	struct ALVec3 {

		ALfloat values[3];

		ALfloat* x = &values[0];
		ALfloat* y = &values[1];
		ALfloat* z = &values[2];

		ALVec3() {

			values[0] = 0.0f;
			values[1] = 0.0f;
			values[2] = 0.0f;

		}

		ALVec3(float x_, float y_, float z_) {

			values[0] = x_;
			values[1] = y_;
			values[2] = z_;

		}

		ALVec3(glm::vec3 gvec) {

			values[0] = gvec.x;
			values[1] = gvec.y;
			values[2] = gvec.z;

		}

		inline ALVec3& operator = (const glm::vec3& gvec) {

			values[0] = gvec.x;
			values[1] = gvec.y;
			values[2] = gvec.z;

		}

	};

	struct Sound {

		Sound(ALuint* buffer_) {

			buffer = *buffer_;

			alGenSources(1, &source);

			alSourcei(source, AL_BUFFER, buffer);

			std::string tag = "";

		}

		~Sound() {

			alDeleteSources(1, &source);

		}

		void play() {

			alSourcePlay(source);

		}

		void stop() {

			alSourceStop(source);
			alSourceRewind(source);

		}

		void pause() {

			alSourcePause(source);

		}

		bool isPlaying() {

			ALint state;
			alGetSourcei(source, AL_SOURCE_STATE, &state);

			if (state == AL_PLAYING)
				return true;
			else
				return false;

		}

	private:

		ALuint buffer;
		ALuint source;
		ALuint state;

	};

	struct Texture
	{

		GLuint textureID = 0;
		glm::vec2 size = glm::vec2();
		std::string name = "";

		Texture* copy() const {

			return new Texture(*this);

		}

		~Texture() {

			glDeleteTextures(1, &textureID);

		}

	};

	struct AssetFile {

	private:
		friend class AssetHandler;

		RKGBin::file header;

		std::map < std::string, Texture*> textures = std::map<std::string, Texture*>();
		std::map<std::string, ALuint*>sounds = std::map<std::string, ALuint*>();

		FILE* filePointer;
		
		bool assetsLoaded = false;

		Texture* createTexture(const SDL_Surface* surface, std::string name) {

			if (surface == nullptr) {
				return nullptr;
			}

			HARIKEN::Texture* t = new HARIKEN::Texture();

			t->name = name;

			t->size = glm::vec2(surface->w, surface->h);

			glGenTextures(1, &t->textureID);

			if (t->textureID == 0) {

				switch (glGetError()) {

				case GL_NO_ERROR:
					break;

				case GL_INVALID_ENUM:
					std::cout << "An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
					break;

				case GL_INVALID_VALUE:
					std::cout << "A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
					break;

				case	 GL_INVALID_OPERATION:
					std::cout << "The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
					break;

				case GL_INVALID_FRAMEBUFFER_OPERATION:
					std::cout << "The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag." << std::endl;
					break;

				case GL_OUT_OF_MEMORY:
					std::cout << "There is not enough memory left to execute the command.The state of the GL is undefined, except for the state of the error flags, after this error is recorded." << std::endl;
					break;

				case GL_STACK_UNDERFLOW:
					std::cout << "An attempt has been made to perform an operation that would cause an internal stack to underflow." << std::endl;
					break;

				case GL_STACK_OVERFLOW:
					std::cout << "An attempt has been made to perform an operation that would cause an internal stack to overflow." << std::endl;
					break;

				default:
					break;

				}

			}

			glBindTexture(GL_TEXTURE_2D, t->textureID);

			int mode = GL_RGB;

			if (surface->format->BytesPerPixel == 4) {

				mode = GL_RGBA;

			}

			glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);

			return t;

		}

		void loadAssets() {

			if (assetsLoaded)
				return;

			std::vector<RKGBin::image> binImages;
			std::vector<RKGBin::sound> binSounds;

			RKGBin::RKGBinary::readAssets(header, filePointer, &binImages, &binSounds);

			for (size_t j = 0; j < binImages.size(); j++) {

				textures[binImages[j].name] = createTexture(binImages[j].surface, binImages[j].name);

			}

			for (size_t j = 0; j < binSounds.size(); j++) {

				sounds[binSounds[j].name] = new ALuint(binSounds[j].buffer);

			}

			assetsLoaded = true;

		}

		friend class GameObject;
		friend class UIObject;
		friend class AssetHandler;

		std::map<GameObject*, int> associatedObjects;
		std::map<UIObject*, int> associatedUIs;

		void keepLoaded() {

			associatedObjects[nullptr] = 0;
			associatedUIs[nullptr] = 0;

		}

		void associate(GameObject* object) {

			associatedObjects[object] = 0;

		}

		void associate(UIObject* UI) {

			associatedUIs[UI] = 0;

		}

		void unloadAssets() {

			while (!textures.empty()) {

				delete textures.begin()->second;
				textures.erase(textures.begin());

			}

			while (!sounds.empty()) {

				alDeleteBuffers(1, sounds.begin()->second);
				delete sounds.begin()->second;
				sounds.erase(sounds.begin());

			}

			assetsLoaded = false;

		}

		void disassociate(GameObject* object) {

			if (associatedObjects.find(object) != associatedObjects.end())
				associatedObjects.erase(object);

			//if (associatedObjects.empty() && associatedUIs.empty())
				//unloadAssets();

		}

		void disassociate(UIObject* UI) {

			if (associatedUIs.find(UI) != associatedUIs.end())
				associatedUIs.erase(UI);

			//if (associatedObjects.empty() && associatedUIs.empty())
				//unloadAssets();

		}

	public:

		std::string getName() const {

			return header.fileName;

		}

		int getTextureAmount() const {

			return header.imageAmount;

		}

		int getSoundAmount() const {

			return header.soundAmount;

		}

		const Texture* getTexture(std::string name) {

			if (textures.find(name) != textures.end())
				return const_cast<Texture*>(textures[name]);

			else
				return nullptr;

		}

		Sound* getSound(std::string name) {
			
			if(sounds.find(name) != sounds.end())
				return new Sound(sounds[name]);

			else
				return nullptr;

		}

	};

	class AssetHandler
	{

	public:

		static AssetHandler* GetInstance();

		AssetHandler(const AssetHandler&) = delete; 
		AssetHandler(AssetHandler&&) = delete;
		AssetHandler& operator = (const AssetHandler&) = delete;
		AssetHandler& operator = (AssetHandler&&) = delete;

	private:

		AssetHandler();
		~AssetHandler();

		static std::unique_ptr<AssetHandler> assetInstance;
		friend std::default_delete<AssetHandler>;

		std::map < std::string, AssetFile*> assetFiles = std::map<std::string, AssetFile*>();
		
		void loadCore();

	private:

		friend class SceneManager;
		void loadAssetList(HGLRC threadContext);

	private:

		friend class GameObject;
		friend class UIObject;
		friend class ParticleEffects;
		AssetFile* getAssetFile(std::string name);

	};

}