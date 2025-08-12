#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <SDL.h>
#include <memory>

#include "GameObject.h"

namespace dae {
    class AnimationComponent final: public Component {
    public:
        AnimationComponent(GameObject* owner, std::shared_ptr<Texture2D> texture, int frameWidth, int frameHeight, int numFrames, float frameTime);
        void Update(float deltaTime) override;

        void Render() const override;

        void SetFrameYOffset(int yOffset) { m_FrameYOffset = yOffset; }

        void SetSize(glm::vec2 size);
        void SetSize(float width, float height);

    	void SetFacingLeft(bool facingLeft) { m_FacingLeft = facingLeft; }
        bool IsFacingLeft() const { return m_FacingLeft; }
    private:
        std::shared_ptr<Texture2D> m_Texture;
        int m_FrameWidth;
        int m_FrameHeight;
        int m_NumFrames;
        int m_CurrentFrame{ 0 };
        float m_FrameTime;
        float m_ElapsedTime{ 0.0f };

        float m_RenderWidth{ 0 };
        float m_RenderHeight{ 0 };
        bool m_FacingLeft{ false };

		int m_FrameYOffset{ 0 };
    };
}

