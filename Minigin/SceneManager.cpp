#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	if (m_activeScene)
		m_activeScene->Update(deltaTime);
}
void dae::SceneManager::FixedUpdate(float fixedTimeStep)
{
	if (m_activeScene)
		m_activeScene->FixedUpdate(fixedTimeStep);
}
void dae::SceneManager::Render()
{
	if (m_activeScene)
		m_activeScene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::SetActiveScene(const std::string& scene)
{
	for (size_t i = 0; i < m_scenes.size(); ++i)
	{
		if (m_scenes[i]->getSceneName() == scene)
		{
			m_activeScene = m_scenes[i];
			return;
		}
	}
}
