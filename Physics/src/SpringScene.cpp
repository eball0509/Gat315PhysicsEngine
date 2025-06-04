#include "SpringScene.h"
#include "Body.h"
#include "../../build/external/raylib-master/src/raymath.h"
#include "MathUtils.h"
#include "raygui.h"
#include "World.h"
#include "gui.h"
#include <iostream>

void SpringScene::Initialize()
{
	m_camera = new SceneCamera({ m_width / 2.0f, m_height / 2.0f });
	Body* head = new Body({ 3, 0 }, { 0, 0 }, 0.25f, WHITE);

	m_world = new World();
	m_world->Initialize(Vector2{ 0, -9.81f }, 30);

}

void SpringScene::Update()
{
	GUI::Update();

	float dt = GetFrameTime();

	if (GUI::resetSimulation)
	{

		if (m_world)
		{
			m_world->DestroyAll();
		}

		m_selected = nullptr;
		m_connect = nullptr;
		
		GUI::resetSimulation = false;
	}

	if (!GUI::mouseOverGUI)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			Body::Type type = (Body::Type)(GUI::bodyTypeActive);
			Body* body = m_world->CreateBody(type, position, GUI::massValue, GUI::sizeValue, ColorFromHSV(randomf(360), 1, 1));

			body->damping = GUI::dampingValue;
			body->gravityScale = GUI::gravityScaleValue;
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selected = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}

		if (m_selected)
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				m_connect = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else
			{
				if (m_selected && m_connect && m_selected != m_connect)
				{
					float distance = Vector2Distance(m_selected->position, m_connect->position);
					m_world->CreateSpring(m_selected, m_connect, distance, GUI::stiffnessValue, GUI::springDampingValue);
				}
				m_selected = nullptr;
				m_connect = nullptr;
			}
		}
	}

	if (m_world)
	{
		m_world->Step(dt);
	}

	for (auto body : m_world->GetBodies())
	{
		if (body->type != Body::Type::Dynamic)
		{
			continue;
		}

		AABB aabb = body->GetAABB();
		AABB worldAABB = m_camera->GetAABB();

		if ((aabb.min().y) < worldAABB.min().y)
		{
			float overlap = (worldAABB.min().y - aabb.min().y);
			body->position.y += 2 * overlap;
			body->velocity.y *= -body->restitution;
		}
		else if ((aabb.max().y) > worldAABB.max().y)
		{
			float overlap = (worldAABB.max().y - aabb.max().y);
			body->position.y += 2 * overlap;
			body->velocity.y *= -body->restitution;
		}

		if ((aabb.min().x) < worldAABB.min().x)
		{
			float overlap = (worldAABB.min().x - aabb.min().x);
			body->position.x += 2 * overlap;
			body->velocity.x *= -body->restitution;
		}
		else if (aabb.max().x > worldAABB.max().x)
		{
			float overlap = (worldAABB.max().x - aabb.max().x);
			body->position.x += 2 * overlap;
			body->velocity.x *= -body->restitution;
		}
	}
}

void SpringScene::FixedUpdate()
{
	m_world->Step(Scene::fixedTimeStep);
}

void SpringScene::Draw()
{
	m_camera->BeginMode();

	m_world->Draw(*this);

	if (m_selected)
	{
		DrawCircleLine(m_selected->position, m_selected->size, YELLOW);
	}

	m_camera->EndMode();
}


void SpringScene::DrawGUI()
{
	GUI::Draw();
}
