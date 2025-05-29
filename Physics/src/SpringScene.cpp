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

	float theta = randomf(0, 360);


	if (!GUI::mouseOverGUI)
	{

		//Place a body
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{

			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			Body::Type type = (Body::Type)(GUI::bodyTypeActive);
			Body* body = m_world->CreateBody(type, position, GUI::massValue, GUI::sizeValue, ColorFromHSV(randomf(360), 1, 1));

			float offset = randomf(-1, 1);

			float x = cos(theta);
			float y = sin(theta);

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
			else {
				if (m_selected && m_connect)
				{
					float distance = Vector2Distance(m_selected->position, m_connect->position);
					m_world->CreateSpring(m_selected, m_connect, distance, GUI::stiffnessValue, GUI::springDampingValue);
				}
				m_selected = nullptr;
				m_connect = nullptr;
			}
		}


	}

	//Apply Collision
	for (auto body : m_world->GetBodies())
	{
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -body->damping;

			//TODO: Clamp to left/right
		}


		if (body->position.x < -9)
		{
			body->position.x = -9;
			body->velocity.x *= -body->damping;
		}

		if (body->position.x > 9)
		{
			body->position.x = 9;
			body->velocity.x *= -body->damping;
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
