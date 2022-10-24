#include "stdafx.h"
#include "cnSkyBox.h"

using namespace HARIKEN;

void HARIKEN::cnSkyBox::onCreate()
{
	/*
	SDL_Surface *textureSurface;

	objLoader obj("cube.obj");

	/// Create a shader with attributess
	ShaderHandler::GetInstance()->createShader("scottTexture", "Shaders/texture");

	meshes.push_back(new Mesh(obj.vertices,));

	/* For the skull
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	textureSurface = IMG_Load("skull_texture.jpg");
	if (textureSurface == nullptr) {
		std::cout << "Can't load image" << std::endl;
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureSurface->w, textureSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);

	//GLuint loc = loadTextureRAW("IMG/skull_texture.jpg", 2048, 2048);
	GLuint texture0 = glGetUniformLocation(shader->getProgram(), "myTexture0");

	glUniform1i(glGetUniformLocation(shader->getProgram(), "myTexture0"), texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//positive X
	textureSurface = IMG_Load("IMG/CN/posx.jpg");
	if (textureSurface == nullptr) {
		std::cout << "Can't load image" << std::endl;
		return;
	}

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, textureSurface->w, textureSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);

	//negative X
	textureSurface = IMG_Load("IMG/CN/negx.jpg");
	if (textureSurface == nullptr) {
		std::cout << "Can't load image" << std::endl;
		return;
	}

	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, textureSurface->w, textureSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);

	//positive Y
	textureSurface = IMG_Load("IMG/CN/posy.jpg");
	if (textureSurface == nullptr) {
		std::cout << "Can't load image" << std::endl;
		return;
	}

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, textureSurface->w, textureSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);

	//negative Y
	textureSurface = IMG_Load("IMG/CN/negy.jpg");
	if (textureSurface == nullptr) {
		std::cout << "Can't load image" << std::endl;
		return;
	}

	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, textureSurface->w, textureSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);

	//positive Z
	textureSurface = IMG_Load("IMG/CN/posz.jpg");
	if (textureSurface == nullptr) {
		std::cout << "Can't load image" << std::endl;
		return;
	}

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, textureSurface->w, textureSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);

	//negative Z
	textureSurface = IMG_Load("IMG/CN/negz.jpg");
	if (textureSurface == nullptr) {
		std::cout << "Can't load image" << std::endl;
		return;
	}

	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, textureSurface->w, textureSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);

	GLuint texture0 = glGetUniformLocation(shader->getProgram(), "myTexture0");

	glUniform1i(glGetUniformLocation(shader->getProgram(), "myTexture0"), texture);

	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");

	modelMatrix = MMath::translate(0.0f, 0.0f, 10.0f) * MMath::scale(10.0f, 10.0f, 10.0f);
	*/
}

void HARIKEN::cnSkyBox::update()
{
}

const void HARIKEN::cnSkyBox::render()
{
	return void();
}
