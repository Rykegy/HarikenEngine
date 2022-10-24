#pragma once
#include "Scene.h"
#include "Triangle.h"
#include "cubeModel.h"

namespace HARIKEN {

	class Cube : public GameObject
	{
	public:

		void onCreate();

		void update();

	private:

		float angle = 0.0f;
		Model* shape;

	};

}