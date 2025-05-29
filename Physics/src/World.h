#pragma once
#include "Body.h"
#include "Spring.h"
#include <vector>
#include "../../build/external/raylib-master/src/raylib.h"
#include "Contact.h"

class Scene;

using bodies_t = std::vector<Body*>;
using springs_t = std::vector<Spring*>;
using contacts_t = std::vector<Contact>;

class World
{
public:
	World() = default;
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0, -9.81f }, size_t poolSize = 30);

	Body* CreateBody(const Vector2& position, float size, const Color& color);
	Body* CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color);

	Spring* CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness, float damping);

	void Step(float timeStep);
	void Draw(const Scene& scene);
	void DestroyAll();

	inline static Vector2 gravity{ 0, -9.81f };
	inline static float gravitation = 0.15f;
	inline static float springStiffnessMult = 1;
	inline static bool simulate = true;

	bodies_t& GetBodies() { return m_bodies; }


private:
	Vector2 m_gravity;
	bodies_t m_bodies;
	springs_t m_springs;
	contacts_t m_contacts;
};