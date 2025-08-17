#pragma once
#include "Component.h"
#include <vec2.hpp>

namespace dae
{
    class ColliderComponent : public Component {
    public:
        ColliderComponent(GameObject* owner);

        void Update(float /*deltaTime*/) override {}
        void Render() const override {}

        const glm::vec2& GetSize() const;
        void SetSize(float width, float height);
        void SetSize(glm::vec2 size);

        void SetInactive()
        {
            m_Active = false;
        }
		void SetActive()
        {
	        m_Active = true;
        }
    private:
        glm::vec2 m_Size;
		bool m_Active{ true }; 
    };
}

