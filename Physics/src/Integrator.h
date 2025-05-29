#pragma once
#include "Body.h"
#include "../../build/external/raylib-master/src/raymath.h"

inline void ExplicitIntegrator(Body& body, float timeStep)
{
	body.position += body.velocity * timeStep;
	body.velocity += body.acceleration * timeStep;
	body.velocity *= 1 / (1.0f + (body.damping * timeStep)); // Damping
}

inline void SemiImplicitIntegrator(Body& body, float timeStep)
{
	body.velocity += body.acceleration * timeStep;
	body.position += body.velocity * timeStep;
}