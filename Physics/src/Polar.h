#pragma once
#include "../../build/external/raylib-master/src/raylib.h"
#include <cmath>

struct Polar
{
public:
	Polar() = default;

	Polar(float angle, float radius) : angle{ angle }, radius{ radius } {}

	Polar(const Vector2& v) : angle{ std::atan2(v.y, v.x)}, radius{ std::sqrt(v.x * v.x + v.y * v.y)} {}

	Polar& operator = (const Vector2& v)
	{
		angle = std::atan2(v.y, v.x);
		radius = std::sqrt(v.x * v.x + v.y * v.y);


		return *this;
	}

	operator Vector2() const
	{
		Vector2 v;
		v.x = std::cos(angle) * radius;
		v.y = std::sin(angle) * radius;

		return v;
	}

public:
	float angle{ 0 };
	float radius{ 0 };
};
