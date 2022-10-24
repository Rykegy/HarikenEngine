#pragma once
#include <glm.hpp>
#include <cmath>
namespace MATH {

	class VMath2D {

	public:

		inline static float dot(const glm::vec2 &a, const glm::vec2 &b) {
			return a.x * b.x + a.y * b.y;
		}

		static float getMag(const glm::vec2 &vector) {
			return std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
		}

		static float getMagSq(const glm::vec2 &vector) {
			return std::pow(vector.x, 2) + std::pow(vector.y, 2);
		}

		static glm::vec2 getNormaVec(const glm::vec2 &a, const glm::vec2 &b) {

			glm::vec2 line = b - a;

			float basket = line.x;
			line.x = line.y;
			line.y = -basket;

			return line;

		}

		static glm::vec2 noMoreLies(const glm::vec2 &vector) {
			return vector / getMag(vector);
		}

	};

}