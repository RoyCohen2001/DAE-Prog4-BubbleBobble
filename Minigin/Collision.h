#pragma once
#include <vec2.hpp>
#include "ColliderComponent.h"
#include "GameObject.h"

namespace dae {
    class Collision {
    public:
        static bool CheckColliding(const glm::vec2& posA, const glm::vec2& sizeA,
            const glm::vec2& posB, const glm::vec2& sizeB) {
            return posA.x < posB.x + sizeB.x &&
                posA.x + sizeA.x > posB.x &&
                posA.y < posB.y + sizeB.y &&
                posA.y + sizeA.y > posB.y;
        }

        static bool IsColliding(GameObject* objA, GameObject* objB)
        {
            auto* colliderA = objA->GetComponent<ColliderComponent>();
            auto* colliderB = objB->GetComponent<ColliderComponent>();
            if (!colliderA || !colliderB) return false;

            glm::vec3 posA = objA->GetTransform().GetPosition();
            glm::vec2 sizeA = colliderA->GetSize();

            glm::vec3 posB = objB->GetTransform().GetPosition();
            glm::vec2 sizeB = colliderB->GetSize();

            // AABB collision check
            bool xOverlap = posA.x < posB.x + sizeB.x && posA.x + sizeA.x > posB.x;
            bool yOverlap = posA.y < posB.y + sizeB.y && posA.y + sizeA.y > posB.y;

            return xOverlap && yOverlap;
        }
    };
}
