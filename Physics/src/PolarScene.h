// PolarScene.h
#pragma once
#include "Scene.h"
#include "Polar.h"
#include <vector>

class PolarScene : public Scene
{
public:
    PolarScene(int screenWidth, int screenHeight);
    ~PolarScene() override = default;

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void DrawGUI() override;

private:
    float archimedean_a;
    float archimedean_b;

    float cardioid_a;

    float limacon_a;
    float limacon_b;

    float rose_a;
    int rose_k_cos;
    int rose_k_sin;

    float user_a;
    float user_b;
    float user_c;

    Vector2 PolarToScreen(const Polar& polar);

    std::vector<Vector2> GenerateArchimedeanSpiral(float minTheta, float maxTheta, float step);
    std::vector<Vector2> GenerateCardioid(float minTheta, float maxTheta, float step);
    std::vector<Vector2> GenerateLimacon(float minTheta, float maxTheta, float step);
    std::vector<Vector2> GenerateRoseCurve(float minTheta, float maxTheta, float step, float a, int k, bool useCos);
    std::vector<Vector2> GenerateUserCurve(float minTheta, float maxTheta, float step);
};