#pragma once
#include "../../build/external/raylib-master/src/raylib.h"

struct Contact
{
	struct Body* bodyA;
	struct Body* bodyB;

	float restitution;	// restitution of both bodies
	float depth;		// penetration depth
	Vector2 normal;		// normal contact vector
};