#pragma once
//#include "Component.h"
//#include "Texture2D.h"
//#include <SDL.h>
//#include <memory>
//
//#include "GameObject.h"
//#include "Renderer.h"
//
//namespace dae {
//class AnimationComponent : public Component {
//public:
//    AnimationComponent(GameObject* owner, std::shared_ptr<Texture2D> texture, int frameWidth, int frameHeight, int numFrames, float frameTime)
//        : Component(owner), m_Texture(texture), m_FrameWidth(frameWidth), m_FrameHeight(frameHeight), m_NumFrames(numFrames), m_FrameTime(frameTime) {}
//
//    void Update(float deltaTime) override {
//        m_ElapsedTime += deltaTime;
//        if (m_ElapsedTime >= m_FrameTime) {
//            m_ElapsedTime -= m_FrameTime;
//            m_CurrentFrame = (m_CurrentFrame + 1) % m_NumFrames;
//        }
//    }
//
//    void Render() const override {
//        if (!m_Texture) return;
//        auto pos = GetOwner()->GetTransform().GetPosition();
//        SDL_Rect srcRect;
//        srcRect.x = m_CurrentFrame * m_FrameWidth;
//        srcRect.y = 0;
//        srcRect.w = m_FrameWidth;
//        srcRect.h = m_FrameHeight;
//        Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, (float)m_FrameWidth, (float)m_FrameHeight, srcRect);
//    }
//
//private:
//    std::shared_ptr<Texture2D> m_Texture;
//    int m_FrameWidth;
//    int m_FrameHeight;
//    int m_NumFrames;
//    int m_CurrentFrame{0};
//    float m_FrameTime;
//    float m_ElapsedTime{0.0f};
//};
//}
