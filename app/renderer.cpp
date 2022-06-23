

#include "renderer.hpp"
#include <algorithm>

namespace roguelike
{
    void Renderer::Render(std::vector<EntityData*> pEntities)
    {
        std::for_each(pEntities.begin(), pEntities.end(), [this](EntityData* pEntity) {
            this->RenderEntity(pEntity);
        });
    }
}