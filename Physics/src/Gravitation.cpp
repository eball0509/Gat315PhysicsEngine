#include "Gravitation.h"
#include "../../build/external/raylib-master/src/raymath.h"

void ApplyGravitation(bodies_t& bodies, float strength)
{
	for (int i = 0; i < bodies.size(); i++)
	{
		Body* bodyA = bodies[i];
		for (int j = i + 1; j < bodies.size(); j++)
		{
			Body* bodyB = bodies[j];

			Vector2 direction = Vector2Subtract(bodyB->position, bodyA->position);
			float distance = Vector2Length(direction);

			distance = std::max(distance, 1.0f);

			if (distance > 0)
			{
				float force = strength * (bodyA->mass * bodyB->mass) / (distance * distance);

				Vector2 forceDirection = Vector2Scale(Vector2Normalize(direction), force);


				bodyA->ApplyForce(forceDirection);
				bodyB->ApplyForce(Vector2Negate(forceDirection));
			}
		}
	}
}
