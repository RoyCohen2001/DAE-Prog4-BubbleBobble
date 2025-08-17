#pragma once
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Transform.h"
#include "Component.h"
#include "Texture2D.h"

namespace dae
{
    enum class ObjectType
    {
	    Player,
    	Enemy,
    	Bullet,
    	Wall,
        Bubble,
        Bounds
    };

    class GameObject final
    {
    public:
        void FixedUpdate(float fixedTimeStep);
        void Update(float deltaTime);
        void Render() const;

        void SetPosition(float x, float y);
        const Transform& GetTransform() const { return m_Transform; }

        void SetParent(GameObject* parent, bool keepWorldPosition);
        void SetLocalPosition(const glm::vec3& pos);

        // Tag system
        void SetTag(const ObjectType tag) { m_Tag = tag; }
        const ObjectType& GetTag() const { return m_Tag; }

		GameObject* GetParent() const;
        size_t ChildCount() const;
		GameObject* GetChildAt(unsigned int index) const;
        void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);


        GameObject() = default;
        ~GameObject();
        GameObject(const GameObject& other) = delete;
        GameObject(GameObject&& other) = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other) = delete;

        template <typename ComponentType, typename... Args>
        ComponentType* AddComponent(Args&&... args);

        template <typename ComponentType>
        void RemoveComponent();

        template <typename ComponentType>
        ComponentType* GetComponent() const;

        template <typename ComponentType>
        bool HasComponent() const;

    private:
        GameObject* m_Parent;
        std::vector<GameObject*> m_Children;

        Transform m_Transform;

        std::vector<std::unique_ptr<Component>> m_Components;
        std::unordered_map<std::type_index, Component*> m_ComponentMap;


        void SetPositionDirty();
		bool IsChild(GameObject* child) const;
		glm::vec3 GetWorldPosition() const;

        ObjectType m_Tag;

    };

    template <typename ComponentType, typename... Args>
    ComponentType* GameObject::AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must derive from Component");

        auto component = std::make_unique<ComponentType>(this, std::forward<Args>(args)...);
        ComponentType* componentPtr = component.get();
        m_Components.push_back(std::move(component));
        m_ComponentMap[std::type_index(typeid(ComponentType))] = componentPtr;
        return componentPtr;
    }

    template <typename ComponentType>
    void GameObject::RemoveComponent()
    {
        static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must derive from Component");

        auto it = std::remove_if(m_Components.begin(), m_Components.end(),
            [](const std::unique_ptr<Component>& component)
            {
                return typeid(*component) == typeid(ComponentType);
            });

        if (it != m_Components.end())
        {
            m_ComponentMap.erase(std::type_index(typeid(ComponentType)));
            m_Components.erase(it, m_Components.end());
        }
    }

    template <typename ComponentType>
    ComponentType* GameObject::GetComponent() const
    {
        static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must derive from Component");
			
        auto it = m_ComponentMap.find(std::type_index(typeid(ComponentType)));
        if (it != m_ComponentMap.end())
        {
            return static_cast<ComponentType*>(it->second);
        }
        return nullptr;
    }

    template <typename ComponentType>
    bool GameObject::HasComponent() const
    {
        static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must derive from Component");

        return m_ComponentMap.find(std::type_index(typeid(ComponentType))) != m_ComponentMap.end();
    }
}
