#pragma once
#include <string>

namespace dae {
    class Scene;

    class LevelLoader final {
    public:
        static void LoadLevel(const std::string& filename, Scene& scene, int blockIndex = 0);
    };
}