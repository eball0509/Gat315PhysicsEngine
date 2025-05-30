#include "Collision.h"
#include "Contact.h"
#include "World.h"
#include "../../build/external/raylib-master/src/raymath.h"
#include "MathUtils.h"

bool Intersects(Body* bodyA, Body* bodyB)
{
	float distance = Vector2Distance(bodyA->position, bodyB->position);
	float radius = bodyA->size + bodyB->size;

	return (distance <= radius);
}

void CreateContacts(const bodies_t& bodies, contacts_t& contacts)
{
	for (int i = 0; i < bodies.size(); i++)
	{
		Body* bodyA = bodies[i];
		for (int j = i + 1; j < bodies.size(); j++)
		{
			Body* bodyB = bodies[j];
			if ((bodyA->type != Body::Type::Dynamic && bodyB->type != Body::Type::Dynamic)) continue;

			if (Intersects(bodyA, bodyB))
			{
				Contact contact;
				contact.bodyA = bodyA;
				contact.bodyB = bodyB;

				Vector2 direction = Vector2Subtract(bodyA->position, bodyB->position);
				float distanceSqr = Vector2LengthSqr(direction);
				if (distanceSqr <= EPSILON)
				{
					direction = Vector2{ randomf(-0.05f, 0.05f), randomf(-0.05f, 0.05f) };
					distanceSqr = Vector2LengthSqr(direction);
				}

				float distance = sqrtf(distanceSqr);
				float radius = bodyA->size + bodyB->size;
				contact.depth = radius - distance;
				contact.normal = Vector2Normalize(direction);
				contact.restitution = 0.5f;

				contacts.push_back(contact);
			}
		}
	}
}

void SeparateContacts(contacts_t& contacts)
{
	for (auto& contact : contacts)
	{
		float totalInverseMass = contact.bodyA->invMass + contact.bodyB->invMass;

		if (totalInverseMass == 0 || contact.depth == 0)
		{
			continue;
		}

		Vector2 separation = Vector2Scale(contact.normal, contact.depth / totalInverseMass);

		contact.bodyA->position = Vector2Add(contact.bodyA->position, Vector2Scale(separation, contact.bodyA->invMass));
		contact.bodyB->position = Vector2Subtract(contact.bodyB->position, Vector2Scale(separation, contact.bodyB->invMass));
	}
}

void ResolveContacts(contacts_t& contacts)
{
	for (auto& contact : contacts)
	{
		// Compute relative velocity: velocity of bodyA relative to bodyB
		Vector2 rv = Vector2Subtract(contact.bodyA->velocity, contact.bodyB->velocity);

		// Project relative velocity onto the contact normal (nv is the normal velocity)
		float nv = Vector2DotProduct(rv, contact.normal);

		// Skip if bodies are already separating or not moving towards each other along the normal
		if (nv > 0) continue;

		// Compute impulse magnitude
		// totalInverseMass is the sum of inverse masses, used to distribute impulse
		float totalInverseMass = contact.bodyA->invMass + contact.bodyB->invMass;
		if (totalInverseMass == 0) continue; // Avoid division by zero if both bodies are static

		// Calculate the impulse magnitude (J).
		// The -(1 + restitution) factor accounts for the bounce.
		// Dividing by totalInverseMass ensures correct impulse distribution.
		float impulseMagnitude = -(1 + contact.restitution) * nv / totalInverseMass;

		// Compute impulse vector: direction is the normal, magnitude is 'impulseMagnitude'
		Vector2 impulse = Vector2Scale(contact.normal, impulseMagnitude);

		// Apply impulses to both bodies
		// bodyA receives the impulse in the direction of the normal
		contact.bodyA->ApplyForce(impulse, Body::ForceMode::Impulse);
		// bodyB receives an equal and opposite impulse
		contact.bodyB->ApplyForce(Vector2Scale(impulse, -1.0f), Body::ForceMode::Impulse);
	}
}
