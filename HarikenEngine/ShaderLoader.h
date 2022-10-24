/**************************************************************
Loader uised to read shaders (Compute shaders and functionality untested).
**************************************************************/

#pragma once

#include <glew.h>
#include <fstream>
#include <sstream>
#include <vector>

GLuint LoadCShader(const char * path);
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);