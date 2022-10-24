/****************************************
Singleton to load and distribute GLSL shader files.
****************************************/

#pragma once
#include <memory>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <glew.h>
#include "ShaderLoader.h"

struct Shader
{

	GLuint shaderID = 0;
	std::string vertFileName = "";
	std::string fragFileName = "";

};

class ShaderHandler
{
public:

	static ShaderHandler* GetInstance();

	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator = (const ShaderHandler&) = delete;
	ShaderHandler& operator = (ShaderHandler&&) = delete;

	void createShader(const std::string& ShaderName_, const std::string& ShaderFileName_);
	static const GLuint getShader(const std::string& shaderName_);

	static std::map < std::string, Shader*> shaders;

private:
	ShaderHandler();
	virtual ~ShaderHandler();

	static std::unique_ptr<ShaderHandler> shaderInstance;
	friend std::default_delete<ShaderHandler>;

};

