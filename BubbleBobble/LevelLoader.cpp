#include "LevelLoader.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include <fstream>
#include <memory>
#include <iostream>
#include "ColliderComponent.h"
#include "Util.h"

namespace dae {
	std::vector<std::shared_ptr<dae::GameObject>> LevelLoader::m_SolidBlocks;

    void LevelLoader::LoadLevel(const std::string& filename, Scene& scene, int blockIndex)
    {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        int y = 2;
        

        auto tex = ResourceManager::GetInstance().LoadTexture("Blocks.png");
        const int blockSize = tex->GetSize().x / 3;
        SDL_Rect srcRect{ blockIndex * blockSize, 0, blockSize, blockSize };

        const float scale = 2.0f;

        while (std::getline(file, line)) {
            for (int x = 0; x < static_cast<int>(line.size()); ++x) {
                char cell = line[x];
                if (cell == '0') continue;

                if (cell == '1' || cell == '2')
                {
                    auto obj = std::make_shared<GameObject>();
                    obj->SetPosition(static_cast<float>(x * blockSize) * scale, static_cast<float>(y * blockSize) * scale);
                    auto* renderComp = obj->AddComponent<RenderComponent>(tex);
                    renderComp->SetSourceRect(srcRect);
                    renderComp->SetSize(static_cast<float>(blockSize) * scale, static_cast<float>(blockSize) * scale);

                    auto* collider = obj->AddComponent<ColliderComponent>();
                    collider->SetSize(glm::vec2(static_cast<float>(blockSize) * scale, static_cast<float>(blockSize) * scale));

                	m_SolidBlocks.push_back(obj);

                    scene.Add(obj);
                }
            }
            ++y;
        }
    }

    const std::vector<std::shared_ptr<GameObject>>& LevelLoader::GetSolidBlocks()
    {
        return m_SolidBlocks;
    } 

}