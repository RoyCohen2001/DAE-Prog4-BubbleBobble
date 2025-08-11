#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

namespace dae {
    class Scene;

    class LevelLoader final {
    public:
        static void LoadLevel(const std::string& filename, Scene& scene, int blockIndex = 0);
        static const std::vector<std::shared_ptr<GameObject>>& GetSolidBlocks();
    private:
        static std::vector<std::shared_ptr<GameObject>> m_SolidBlocks;
    };
}