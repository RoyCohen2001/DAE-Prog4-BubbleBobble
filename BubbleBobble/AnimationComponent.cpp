#include "AnimationComponent.h"

#include <stdexcept>

#include "GameActor.h"
#include "Renderer.h"
#include "GameObject.h"


dae::AnimationComponent::AnimationComponent(GameObject* owner, std::shared_ptr<Texture2D> texture, int frameWidth, int frameHeight, int numFrames, float frameTime)
	: Component(owner), m_Texture(texture), m_FrameWidth(frameWidth), m_FrameHeight(frameHeight), m_NumFrames(numFrames), m_FrameTime(frameTime)
{
}
void dae::AnimationComponent::Update(float deltaTime)
{
	m_ElapsedTime += deltaTime;
	if (m_ElapsedTime >= m_FrameTime) {
		m_ElapsedTime -= m_FrameTime;
		m_CurrentFrame = (m_CurrentFrame + 1) % m_NumFrames;
	}
}

void dae::AnimationComponent::Render() const
{
    if (!m_Texture) return;
    auto pos = GetOwner()->GetTransform().GetPosition();
    SDL_Rect srcRect;
    srcRect.x = m_CurrentFrame * m_FrameWidth;
    srcRect.y = 0;
    srcRect.w = m_FrameWidth;
    srcRect.h = m_FrameHeight;
    float width = m_RenderWidth > 0 ? m_RenderWidth : static_cast<float>(m_FrameWidth);
    float height = m_RenderHeight > 0 ? m_RenderHeight : static_cast<float>(m_FrameHeight);

    auto* actor = GetOwner()->GetComponent<GameActor>();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (actor && actor->IsFacingLeft())
        flip = SDL_FLIP_HORIZONTAL;

    Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, width, height, srcRect, flip);

}

void dae::AnimationComponent::SetSize(glm::vec2 size)
{
    m_RenderWidth = size.x;
    m_RenderHeight = size.y;
}

void dae::AnimationComponent::SetSize(float width, float height)
{
    m_RenderWidth = width;
    m_RenderHeight = height;
}
