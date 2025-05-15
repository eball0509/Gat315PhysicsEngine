#include "trigonometry_scene.h"

void TrigonometryScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
}

void TrigonometryScene::Update()
{
}

void TrigonometryScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);
	DrawCircleV(m_camera->WorldToScreen(Vector2{ 0, 0 }), m_camera->WorldToScreen(1), RED);

	m_camera->EndMode();
}

void TrigonometryScene::DrawGUI()
{
}
