#pragma once
#include "TextComponent.h"
#include <chrono>


namespace dae
{
    class FPSComponent final : public TextComponent
    {
    public:
        FPSComponent(GameObject* owner, std::shared_ptr<Font> font);
        void Update(float deltaTime) override;

    private:
        int m_FrameCount;
        std::chrono::high_resolution_clock::time_point m_FPSTimer;
    };
}

