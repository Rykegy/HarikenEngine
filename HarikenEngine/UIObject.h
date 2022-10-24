/**********************************************************
Similar to a GameObject except with no collision and physics functions.
**********************************************************/

#pragma once

#include<string>

#include "imageFrame.h"
#include "InputSys.h"
#include "WindowSys.h"
#include "FontHandler.h"

namespace HARIKEN {

	class SceneManager;
	class InputSys;
	class WindowSys;

	class UIObject
	{

	public:

		enum Align {

			center,
			left,
			right,
			top,
			bottom

		};

	private:

		struct Alignment {

			Align horizontal = center;
			Align vertical = center;

		};

		std::map<AssetFile*, int> filesUsed;

	public:
		UIObject();
		~UIObject();

		void init(Scene* gameScene);

		virtual void onCreate() = 0;
		virtual void update() = 0;
		void afterUpdate();
		void render();

		enum UIType
		{

			Text,
			Image

		};

		const glm::vec2 getPosition();
		void setPosition(float newX, float newY);
		void setPosition(glm::vec2 newPosition);

		glm::vec2 getSize();

		glm::vec2 getImagePosition();
		glm::vec2 getImagePosition(int index);

		void setScale(glm::vec3 scale_);
		glm::vec3 getScale();

		void addTag(std::string tag_); 
		bool hasTag(std::string tag_);

		void setImg(const Texture* texture);
		void setFont(std::string path);
		void setText(std::string text_, int size_, glm::vec3 color_);
		void setText(std::u16string text_, int size_, glm::vec3 color_);

		AssetFile* getAssetFile(std::string name);

		Alignment alignment;

		int layer = 0;

		bool isActive = true;
		bool willRender = true;

	protected:

		bool onClick();
		bool onMouseOver();

		const Texture* getImage();

		Scene* GameScene;
		glm::vec2 windowSize;

		Time* time;
		InputSys* InputSys;
		WindowSys* Window;
		SceneManager* sceneManager;
		FontHandler* fontHandler;
		Camera* camera;
		AssetHandler* assetHandler;

	private:

		friend class SceneManager;

		struct setTextRequest {

			std::u16string text;
			int size;
			glm::vec3 color;

			bool requestMade = false;

			setTextRequest() {

				requestMade = false;

			}

			setTextRequest(std::u16string text_, int size_, glm::vec3 color_) {

				text = text_;
				size = size_;
				color = color_;

				requestMade = true;

			}

		};

		UIType type = UIType::Image;

		const Texture* image;
		std::vector<imageFrame*> model;
		std::u16string text;
		int fontSize;

		std::vector<glm::vec2> imagepos;
		glm::vec2 position;
		glm::vec3 scale = glm::vec3(1.0f);

		std::string pathName;
		std::string fontName;

		std::vector<std::string>tag;

		ShaderHandler* shaderHandler;
		std::map<char16_t, Character>* characterMap;

		GLuint program;
		GLuint colorLoc;
		GLuint texLoc;
		GLuint projectionLoc;

		glm::vec3 color;

		GLuint vao;
		GLuint vbo;

	private:

		friend class Scene;

		void realSetText();

		setTextRequest request;

	};

}