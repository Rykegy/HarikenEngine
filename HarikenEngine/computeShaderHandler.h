/**********************************************************************
Part of a currently unimplemented idea of using Compute shaders to handle particles.
**********************************************************************/

#pragma once
#include <memory>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <glew.h>
#include "ShaderLoader.h"

namespace HARIKEN {

	struct computeShader {

		GLuint cShaderID = 0;
		std::string path = "";

	};

	class computeShaderHandler
	{
	public:

		static computeShaderHandler* GetInstance();

		computeShaderHandler(const computeShaderHandler&) = delete;
		computeShaderHandler(computeShaderHandler&&) = delete;
		computeShaderHandler& operator = (const computeShaderHandler&) = delete;
		computeShaderHandler& operator = (computeShaderHandler&&) = delete;

		void createCShader(const std::string& ShaderName_, const std::string& ShaderFileName_);
		static const GLuint getCShader(const std::string& shaderName_);

		static std::map < std::string, computeShader*> shaders;

	private:

		computeShaderHandler();
		~computeShaderHandler();

		static std::unique_ptr<computeShaderHandler> computeShaderInstance;
		friend std::default_delete<computeShaderHandler>;

	};

}