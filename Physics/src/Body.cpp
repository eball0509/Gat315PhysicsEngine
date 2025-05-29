#include "Body.h"
#include "Integrator.h"
#include "../../build/external/raylib-master/src/raymath.h"
#include "World.h"

void Body::Step(float dt)
{
	if (type != Type::Dynamic) return;
	force += (World::gravity * gravityScale) * mass;
	acceleration = force * inverseMass;

	SemiImplicitIntegrator(*this, dt);
}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}

void Body::ApplyForce(const Vector2& force)
{
	this->force += force;

}