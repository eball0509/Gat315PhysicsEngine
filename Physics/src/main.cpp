#include "../../build/external/raylib-master/src/raylib.h"
#include "trigonometry_scene.h"
#include "VectorScene.h"
#include "SpringScene.h"
#include "PolarScene.h"
#include "../../include/resource_dir.h"

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(1280, 720, "Hello Raylib");

	SearchAndSetResourceDir("resources");

	Texture wabbit = LoadTexture("wabbit_alpha.png");

	Scene* scene = new SpringScene("Scene", 1280, 720);

	scene->Initialize();

	float timeAccumlator = 0.0f;
	while (!WindowShouldClose())		
	{
		scene->Update();
		timeAccumlator += std::min(GetFrameTime(), 0.5f);

		while (timeAccumlator >= Scene::fixedTimeStep)
		{
			scene->FixedUpdate();
			timeAccumlator -= Scene::fixedTimeStep;
		}
		scene->FixedUpdate();
		scene->BeginDraw();
		scene->Draw();
		scene->DrawGUI();
		scene->EndDraw();
	}

	UnloadTexture(wabbit);
	CloseWindow();
	return 0;
}