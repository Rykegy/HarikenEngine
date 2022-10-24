#include "stdafx.h"
#include "computeShaderHandler.h"

using namespace HARIKEN;

std::map<std::string, computeShader*> computeShaderHandler::shaders = std::map < std::string, computeShader*>();
std::unique_ptr<computeShaderHandler> computeShaderHandler::computeShaderInstance = nullptr;


computeShaderHandler::computeShaderHandler()
{
}


computeShaderHandler::~computeShaderHandler()
{
}

computeShaderHandler * HARIKEN::computeShaderHandler::GetInstance()
{
	if (computeShaderInstance.get() == nullptr)
		computeShaderInstance.reset(new computeShaderHandler());

	return computeShaderInstance.get();
}

void HARIKEN::computeShaderHandler::createCShader(const std::string & ShaderName_, const std::string & ShaderFileName_)
{

	if (getCShader(ShaderName_) != 0)
		return;

	computeShader* s = new computeShader();

	std::string path = ShaderFileName_ + ".glsl";

	s->path = path.c_str();

	s->cShaderID = LoadCShader(s->path.c_str());

	shaders[ShaderName_] = s;

}

const GLuint HARIKEN::computeShaderHandler::getCShader(const std::string & shaderName_)
{

	if (shaders.find(shaderName_.c_str()) != shaders.end())
		return shaders[shaderName_]->cShaderID;

	else
		return 0;

}
