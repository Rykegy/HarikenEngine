#include "stdafx.h"
#include "ShaderHandler.h"

std::map<std::string, Shader*> ShaderHandler::shaders = std::map < std::string, Shader*>();
std::unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;

ShaderHandler::ShaderHandler()
{
}


ShaderHandler::~ShaderHandler()
{
}

ShaderHandler * ShaderHandler::GetInstance()
{

	if (shaderInstance.get() == nullptr)
		shaderInstance.reset(new ShaderHandler());

	return shaderInstance.get();

}

void ShaderHandler::createShader(const std::string & ShaderName_, const std::string & ShaderFileName_)
{

	if (getShader(ShaderName_) != 0)
		return;

	Shader* s = new Shader();

	std::string frag = "ASSET/GLSL/" + ShaderFileName_ + "Frag.glsl";
	std::string vert = "ASSET/GLSL/" + ShaderFileName_ + "Vert.glsl";

	s->fragFileName = frag.c_str();
	s->vertFileName = vert.c_str();

	s->shaderID = LoadShaders(s->vertFileName.c_str(), s->fragFileName.c_str());

	shaders[ShaderName_] = s;

}

const GLuint ShaderHandler::getShader(const std::string & shaderName_)
{

	if (shaders.find(shaderName_.c_str()) != shaders.end())
		return shaders[shaderName_]->shaderID;

	else
		return 0;

}
