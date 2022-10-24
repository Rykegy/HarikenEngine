/**************************************************
Loader used to load MTL files to be used to create 3D models.
**************************************************/

#pragma once
#include <vector>
#include <glm.hpp>
#include <string> 
#include <sstream> 
#include "Model.h"

namespace HARIKEN {

	class mtlLoader
	{
	public:
		~mtlLoader();

		std::vector<mtl> mtlList;

		mtlLoader(const mtlLoader&) = delete;  
		mtlLoader(mtlLoader&&) = delete;     
		mtlLoader& operator=(const mtlLoader&) = delete; 
		mtlLoader& operator=(mtlLoader&&) = delete;   

		mtlLoader(const char* path);
		bool loadmtl(const char* path);
	};

}

