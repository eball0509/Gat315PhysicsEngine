// main.cpp
#include "trigonometry_scene.h"
#include "../../build/external/raylib-master/src/raylib.h"
#include "../../Include/resource_dir.h"
#include "PolarScene.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Polar Curves Demo");

    PolarScene polarScene(screenWidth, screenHeight);

    polarScene.Initialize();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        polarScene.Update();

        polarScene.BeginDraw();
        polarScene.Draw();
        polarScene.DrawGUI();
        polarScene.EndDraw();
    }

    CloseWindow();

    return 0;
}