#pragma once
#include <memory>
#include "Util.h"
#include "Transform.h"
#include "Texture2D.h"
#include "Component.h"
#include "Observer.h"
#include "Subject.h"

namespace dae {
    using Event = int;

    class GameActor final : public Component, public Observer, public Subject
    {
    public:
        GameActor(GameObject* owner, const std::string& path);

        void Update(float deltaTime) override;
        void Render() const override;

        // Observer
        void OnNotify(Event event, GameObject* gameObject) override;

        // Set variables of the actor
        void SetSpeed(float speed);
        void SetPosition(float x, float y);

        glm::vec3 GetPosition() const;

        // Move the actor
        void Move(const glm::vec2& direction);

        // Executables
        void Shoot();
        void Jump();
        void Pause();
        void DropDown();


        virtual ~GameActor() = default;
        GameActor(const GameActor& other) = delete;
        GameActor(GameActor&& other) = delete;
        GameActor& operator=(const GameActor& other) = delete;
        GameActor& operator=(GameActor&& other) = delete;

    private:
        Transform m_Transform;
        std::shared_ptr<Texture2D> m_Texture;
        float m_Speed = 50.f;
        glm::vec2 m_MoveDirection{ 0.0f, 0.0f };

		// Jumping variables
		float m_JumpHeight = 0.0f;
        bool m_IsJumping = false;
        float m_JumpSpeed = 0.0f;
        float m_Gravity = 9.81f; // Gravity constant
		float m_TimeSinceJump = 0.0f; // Time since the jump started

		// shooting variables
		bool m_IsShooting = false;
        float m_ShootCooldown = 0.5f; // Cooldown time in seconds
        float m_TimeSinceLastShot = 0.0f; // Time since the last shot was fired
    };
}
