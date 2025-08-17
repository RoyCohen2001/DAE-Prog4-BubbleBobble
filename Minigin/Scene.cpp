#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

#include "Collision.h"
#include "../BubbleBobble/GameActor.h"

namespace dae
{
	class GameActor;
}

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void dae::Scene::FixedUpdate(float fixedTimeStep)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedTimeStep);
	}
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}

	for (size_t i = 0; i < m_objects.size(); ++i)
	{
		for (size_t j = i + 1; j < m_objects.size(); ++j)
		{
			auto& objA = m_objects[i];
			auto& objB = m_objects[j];

			if (dae::Collision::IsColliding(objA.get(), objB.get()))
			{
				if (auto* actorA = objA->GetComponent<dae::GameActor>())
					actorA->OnCollision(objB.get());
				if (auto* actorB = objB->GetComponent<dae::GameActor>())
					actorB->OnCollision(objA.get());
			}
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

std::string Scene::getSceneName()
{
	return m_name;
}

