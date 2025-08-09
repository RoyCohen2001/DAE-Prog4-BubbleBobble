#include "FPSComponent.h"


dae::FPSComponent::FPSComponent(GameObject* owner, std::shared_ptr<Font> font)
    : TextComponent(owner, "FPS: 0", std::move(font)),
    m_FrameCount(0),
    m_FPSTimer(std::chrono::high_resolution_clock::now())
{
}

void dae::FPSComponent::Update(float deltaTime)
{
    ++m_FrameCount;
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - m_FPSTimer).count();

    if (duration >= 1)
    {
        int fps = static_cast<int>(m_FrameCount / duration);
        SetText("FPS: " + std::to_string(fps));
        m_FrameCount = 0;
        m_FPSTimer = now;
    }

    TextComponent::Update(deltaTime);
}