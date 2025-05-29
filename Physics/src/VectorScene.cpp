#include "VectorScene.h"
#include "Body.h"
#include "../../build/external/raylib-master/src/raymath.h"
#include "MathUtils.h"
#include "raygui.h"
#include "World.h"
#include "gui.h"
#include <iostream>

void VectorScene::Initialize()
{
	m_camera = new SceneCamera({ m_width / 2.0f, m_height / 2.0f });
	Body* head = new Body({ 3, 0 }, { 0, 0 }, 0.25f, WHITE);

	m_world = new World();
	m_world->Initialize(Vector2{ 0, -9.81f }, 30);
}

void VectorScene::Update()
{
	GUI::Update();

	float dt = GetFrameTime();

	float theta = randomf(0, 360);


	if (!GUI::mouseOverGUI && IsMouseButtonPressed(0))
	{
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		//Body::Type type = bodyTypeDropdow

		for (int i = 0; i < 100; i++)
		{
			Body* body = m_world->CreateBody(position, 0.25f, ColorFromHSV(randomf(360), 1, 1));

			float offset = randomf(-1, 1);

			float x = cos(theta);
			float y = sin(theta);

			body->damping = GUI::dampingValue;
			body->mass = GUI::massValue;
			body->size = GUI::sizeValue;
			body->gravityScale = GUI::gravityScaleValue;

			body->type = (Body::Type)(GUI::bodyTypeActive);


			//body->velocity = { x * randomf(1, 3), y * randomf(1, 3)};
			body->velocity = { x * randomf(-4, 4), y * randomf(-3, 3) };
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

void VectorScene::FixedUpdate()
{
	m_world->Step(Scene::fixedTimeStep);
} 

void VectorScene::Draw()
{
	m_camera->BeginMode();

	m_world->Draw(*this);

	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
	GUI::Draw();
}
