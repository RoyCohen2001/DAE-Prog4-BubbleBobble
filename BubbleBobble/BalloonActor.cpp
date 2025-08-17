#include "BalloonActor.h"

#include "GameObject.h"

namespace dae {
    BalloonActor::BalloonActor(GameObject* owner)
        : GameActor(owner)
    {
    }

    void BalloonActor::Update(float /*deltaTime*/)
    {
    }

    void BalloonActor::OnCollision(GameObject* other)
    {
        if (other->GetTag() == ObjectType::Player)
        {
            // pop first
            SetDelete(); 
        }
    }
}
