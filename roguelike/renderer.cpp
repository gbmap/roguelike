#include "renderer.hpp"
#include <algorithm>

namespace roguelike
{
    void Renderer::Render(const std::vector<Entity*> reps) const
    {
        std::for_each(reps.begin(), reps.end(), [this](Entity* e) {
            this->Render(e->GetRepresentation(), e->GetPosition());
        });
    }
}