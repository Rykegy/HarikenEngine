/***************************************
Loader used to create 3D models from OBJ Files.
***************************************/

#pragma once
#include <vector>
#include <glm.hpp>
#include <string> 
#include <sstream> 
#include "Model.h"

namespace HARIKEN {

	class objLoader
	{
	public:
		~objLoader();

		std::vector<vertex> vertices;
		std::vector<std::vector<vertex>> verticesList;

		objLoader(const objLoader&) = delete;  
		objLoader(objLoader&&) = delete;   
		objLoader& operator=(const objLoader&) = delete; 
		objLoader& operator=(objLoader&&) = delete; 

		objLoader(const char* path);
		bool loadObj(const char* path);
	};

}