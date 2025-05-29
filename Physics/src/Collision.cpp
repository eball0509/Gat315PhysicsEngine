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
		float totalInverseMass = contact.bodyA->inverseMass + contact.bodyB->inverseMass;

		if (totalInverseMass == 0 || contact.depth == 0)
		{
			continue;
		}

		Vector2 separation = Vector2Scale(contact.normal, contact.depth / totalInverseMass);

		contact.bodyA->position = Vector2Add(contact.bodyA->position, Vector2Scale(separation, contact.bodyA->inverseMass));
		contact.bodyB->position = Vector2Subtract(contact.bodyB->position, Vector2Scale(separation, contact.bodyB->inverseMass));
	}
}
