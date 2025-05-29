#pragma once
#include "../../build/external/raylib-master/src/raylib.h"
#include "scene.h"


struct Body
{

public:
	enum class Type
	{
		Dynamic,
		Kinematic,
		Static
	};
public:
	Body() = default;

	Body(const Vector2& position, const Vector2& velocity, float size, const Color& color)
		: position{ position }, velocity{ velocity }, size{ size }, color{ color }
	{

	}

	Body(const Vector2& position, float size, const Color& color)
		: position{ position }, size{ size }, color{ color }
	{

	}

	Body(Type type, const Vector2& position, float mass, float size, const Color& color)
		: type{ type }, position{ position }, mass{ mass }, size{ size }, color{ color }
	{
		inverseMass = (type == Type::Dynamic && mass != 0) ? 1.0f / mass : 0.0f;
	}

	void Step(float dt);

	void Draw(const Scene& scene);

	void ApplyForce(const Vector2& force);

	void ClearForce() { force = { 0, 0 }; }
public:
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	Vector2 acceleration{ 0, 0 };
	Vector2 force{ 0, 0 };

	float size = 1;
	float damping = 1;

	float mass = 1;
	float inverseMass = 1;

	float gravityScale = 1;

	Color color = WHITE;

	Type type{ Type::Dynamic };

	Body* next{ nullptr };
	Body* prev{ nullptr };
};