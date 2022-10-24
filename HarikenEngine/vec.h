#pragma once

struct glm::vec2 {

	float x;
	float y;

	glm::vec2() {

		x = 0;
		y = 0;

	};

	glm::vec2(float X, float Y) {

		x = X;
		y = Y;

	};

	glm::vec2 operator + (const glm::vec2 other) const{
		return glm::vec2(x + other.x, y + other.y);
	}

	glm::vec2& operator += (const glm::vec2 other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	glm::vec2 operator - (const glm::vec2 other) const{
		return glm::vec2(x - other.x, y - other.y);
	}

	glm::vec2& operator -= (const glm::vec2 other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	glm::vec2 operator * (const float scale) const {
		return glm::vec2(x * scale, y * scale);
	}

	glm::vec2& operator *= (const float scale) {
		x *= scale;
		y *= scale;
		return *this;
	}

	glm::vec2 operator / (const float scale) const {
		return glm::vec2(x / scale, y / scale);
	}

	glm::vec2& operator /= (const float scale) {
		x /= scale;
		y /= scale;
		return *this;
	}

	const glm::vec2 operator - () const {
		return glm::vec2(-x, -y);
	}

	glm::vec2 normal() {
		return glm::vec2(-y, x);
	}

};