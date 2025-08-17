#include "LevelLoader.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include <fstream>
#include <memory>
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "ZenChanEnemy.h"

namespace dae {
	std::vector<std::shared_ptr<dae::GameObject>> LevelLoader::m_SolidBlocks;

    void LevelLoader::LoadLevel(const std::string& filename, Scene& scene, int blockIndex)
    {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        int y = 2;
        
        // Blocks
        auto blockTexture = ResourceManager::GetInstance().LoadTexture("Blocks.png");
        const int blockSize = blockTexture->GetSize().x / 3;
        SDL_Rect srcRect{ blockIndex * blockSize, 0, blockSize, blockSize };

        // Enemies
        auto EnemyTexture = ResourceManager::GetInstance().LoadTexture("Enemies.png");
        float enemySize = 20.f;

        int EnemyWidthTex = EnemyTexture->GetSize().x / 8;
        int EnemyHeightTex = EnemyTexture->GetSize().y / 4;

        const float scale = 2.0f;

        while (std::getline(file, line)) {
            for (int x = 0; x < static_cast<int>(line.size()); ++x) {
                char cell = line[x];
                if (cell == '0') continue;

                if (cell == '1' || cell == '2')
                {
	                
                    auto obj = std::make_shared<GameObject>();
                    obj->SetPosition(static_cast<float>(x * blockSize) * scale, static_cast<float>(y * blockSize) * scale);
                    auto* renderComp = obj->AddComponent<RenderComponent>(blockTexture);
                    renderComp->SetSourceRect(srcRect);
                    renderComp->SetSize(static_cast<float>(blockSize) * scale, static_cast<float>(blockSize) * scale);

                    auto* collider = obj->AddComponent<ColliderComponent>();
                    collider->SetSize(glm::vec2(static_cast<float>(blockSize) * scale, static_cast<float>(blockSize) * scale));

                	m_SolidBlocks.push_back(obj);

                    if (cell == '1') obj->SetTag(ObjectType::Bounds);
                    if (cell == '2') obj->SetTag(ObjectType::Wall);

                    scene.Add(obj);
                }

                if (cell == '3')
                {
                    auto zenChan = std::make_shared<GameObject>();
                    zenChan->SetTag(ObjectType::Enemy);

					auto* zenChanEnemy = zenChan->AddComponent<ZenChanEnemy>();
                    zenChanEnemy->SetSize(glm::vec2(enemySize, enemySize));
                    zenChanEnemy->SetPosition(static_cast<float>(x) * enemySize, static_cast<float>(y) * enemySize);
					zenChanEnemy->SetPatrolArea(0.f, 800.f); 

                    auto* animatedEnemy = zenChan->AddComponent<AnimationComponent>(EnemyTexture, EnemyWidthTex, EnemyHeightTex, 3, 0.15f);
                    animatedEnemy->SetSize(enemySize, enemySize);

                    auto* collider = zenChan->AddComponent<ColliderComponent>();
                    collider->SetSize(glm::vec2(enemySize, enemySize));

                    scene.Add(zenChan);
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
