#include "Spring.h"
#include "Body.h"
#include "../../build/external/raylib-master/src/raymath.h"

void Spring::ApplyForce(float kMultiplier)
{
	Vector2 direction = bodyA->position - bodyB->position;
	float lengthSqr = Vector2LengthSqr(direction);

	if (lengthSqr <= EPSILON) return;

	float length = sqrtf(lengthSqr);

	float displacement = length - restLength;
	float forceMagnitude = -(k * kMultiplier) * displacement;

	Vector2 nDirection = direction / length;
	Vector2 force = nDirection * forceMagnitude;

	Vector2 dv = bodyA->velocity - bodyB->velocity;
	float dampFactor = Vector2DotProduct(dv, nDirection);
	Vector2 dampingForce = nDirection * dampFactor;

	force -= dampingForce;

	bodyA->ApplyForce(force);
	bodyB->ApplyForce(Vector2Negate(force));
}

void Spring::ApplyForce(const Vector2 position, Body& body, float restLength, float k)
{
	Vector2 direction = position - body.position;
	float lengthSqr = Vector2LengthSqr(direction);

	if (lengthSqr <= EPSILON) return;

	float length = sqrtf(lengthSqr);

	float displacement = length - restLength;
	float forceMagnitude = -k * displacement;

	Vector2 nDirection = direction / length;
	Vector2 force = nDirection * forceMagnitude;

	body.ApplyForce(Vector2Negate(force));
}

void Spring::Draw(const Scene& scene)
{
	scene.DrawLine(bodyA->position, bodyB->position, 3.0f, WHITE);
}


// SpingScene
// if (m_selectedbody)
// if (isMouseButtonDown(MBR) && IsKeyDown(K_L_CTRL))
// if (m_selectedbody->type == Body::Type::Dynamic)
// Vector2 position = m_camera->ScreenToWorld(GetMousePOsition())
// Spring::ApplyForce(position, *m_selectedBody, 0.2f, 15.0f)