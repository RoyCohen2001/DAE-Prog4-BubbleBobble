#pragma once
#include <vec2.hpp>

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
    };
}