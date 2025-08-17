#pragma once
#include "GameActor.h"

namespace dae {
    class BalloonActor : public GameActor
    {
    public:
        BalloonActor(GameObject* owner);

        void Update(float deltaTime) override;
        void Render() const override{}
        void OnCollision(GameObject* other) override;
    };
}

