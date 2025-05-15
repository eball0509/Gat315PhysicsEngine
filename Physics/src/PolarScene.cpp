#include "PolarScene.h"

PolarScene::PolarScene(int screenWidth, int screenHeight) :
    Scene("Polar Curves Scene", screenWidth, screenHeight),
    archimedean_a(10.0f),
    archimedean_b(5.0f),
    cardioid_a(50.0f),
    limacon_a(60.0f),
    limacon_b(30.0f),
    rose_a(40.0f),
    rose_k_cos(5),
    rose_k_sin(4),
    user_a(20.0f),
    user_b(3.0f),
    user_c(0.2f)
{
    // Now the screen dimensions are passed in and stored in the base class
}

void PolarScene::Initialize()
{
}

void PolarScene::Update()
{
}

void PolarScene::Draw()
{
    float minTheta = 0.0f;
    float maxTheta = 10.0f * PI;
    float step = 0.01f;

    //// Draw Archimedean Spiral
    //std::vector<Vector2> spiralPoints = GenerateArchimedeanSpiral(minTheta, maxTheta, step);
    //for (size_t i = 0; i < spiralPoints.size() - 1; ++i)
    //{
    //    DrawLineV(spiralPoints[i], spiralPoints[i + 1], RED);
    //}

    //// Draw Cardioid
    //std::vector<Vector2> cardioidPoints = GenerateCardioid(0.0f, 2.0f * PI, step);
    //for (size_t i = 0; i < cardioidPoints.size() - 1; ++i)
    //{
    //    DrawLineV(cardioidPoints[i], cardioidPoints[i + 1], GREEN);
    //}

    //// Draw Limaçon
    //std::vector<Vector2> limaconPoints = GenerateLimacon(0.0f, 2.0f * PI, step);
    //for (size_t i = 0; i < limaconPoints.size() - 1; ++i)
    //{
    //    DrawLineV(limaconPoints[i], limaconPoints[i + 1], BLUE);
    //}

    //// Draw Rose Curve (cosine)
    //std::vector<Vector2> roseCosPoints = GenerateRoseCurve(0.0f, 2.0f * PI, step, rose_a, rose_k_cos, true);
    //for (size_t i = 0; i < roseCosPoints.size() - 1; ++i)
    //{
    //    DrawLineV(roseCosPoints[i], roseCosPoints[i + 1], YELLOW);
    //}

    //// Draw Rose Curve (sine)
    //std::vector<Vector2> roseSinPoints = GenerateRoseCurve(0.0f, 2.0f * PI, step, rose_a, rose_k_sin, false);
    //for (size_t i = 0; i < roseSinPoints.size() - 1; ++i)
    //{
    //    DrawLineV(roseSinPoints[i], roseSinPoints[i + 1], MAGENTA);
    //}

    // Draw User Generated Curve
    std::vector<Vector2> userPoints = GenerateUserCurve(minTheta, maxTheta, step);
    for (size_t i = 0; i < userPoints.size() - 1; ++i)
    {
        DrawLineV(userPoints[i], userPoints[i + 1], ORANGE);
    }
}

void PolarScene::DrawGUI()
{
}

Vector2 PolarScene::PolarToScreen(const Polar& polar)
{
    float scale = std::min(m_width, m_height) / 200;
    float x = m_width / 2.0f + polar.radius * std::cos(polar.angle) * scale;
    float y = m_height / 2.0f - polar.radius * std::sin(polar.angle) * scale;
    return { x, y };
}

std::vector<Vector2> PolarScene::GenerateArchimedeanSpiral(float minTheta, float maxTheta, float step)
{
    std::vector<Vector2> points;
    for (float theta = minTheta; theta <= maxTheta; theta += step)
    {
        float r = archimedean_a + archimedean_b * theta;
        Polar polarPoint(theta, r);
        points.push_back(PolarToScreen(polarPoint));
    }
    return points;
}

std::vector<Vector2> PolarScene::GenerateCardioid(float minTheta, float maxTheta, float step)
{
    std::vector<Vector2> points;
    for (float theta = minTheta; theta <= maxTheta; theta += step)
    {
        float r = cardioid_a * (1.0f + std::cos(theta));
        Polar polarPoint(theta, r);
        points.push_back(PolarToScreen(polarPoint));
    }
    return points;
}

std::vector<Vector2> PolarScene::GenerateLimacon(float minTheta, float maxTheta, float step)
{
    std::vector<Vector2> points;
    for (float theta = minTheta; theta <= maxTheta; theta += step)
    {
        float r = limacon_a + limacon_b * std::cos(theta);
        Polar polarPoint(theta, r);
        points.push_back(PolarToScreen(polarPoint));
    }
    return points;
}

std::vector<Vector2> PolarScene::GenerateRoseCurve(float minTheta, float maxTheta, float step, float a, int k, bool useCos)
{
    std::vector<Vector2> points;
    for (float theta = minTheta; theta <= maxTheta; theta += step)
    {
        float r;
        if (useCos)
        {
            r = a * std::cos(static_cast<float>(k) * theta);
        }
        else
        {
            r = a * std::sin(static_cast<float>(k) * theta);
        }
        Polar polarPoint(theta, r);
        points.push_back(PolarToScreen(polarPoint));
    }
    return points;
}

std::vector<Vector2> PolarScene::GenerateUserCurve(float minTheta, float maxTheta, float step)
{
    std::vector<Vector2> points;
    for (float theta = minTheta; theta <= maxTheta; theta += step)
    {
        // Example: Another type of spiral
        float r = user_a * std::exp(user_b * theta) * std::cos(user_c * theta);
        Polar polarPoint(theta, r);
        points.push_back(PolarToScreen(polarPoint));
    }
    return points;
}
