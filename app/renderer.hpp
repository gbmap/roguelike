

#ifndef RENDERER_H
#define RENDERER_H

#include "../data.hpp"
#include <vector>

namespace roguelike
{
    class Renderer
    {
    public:
        void Render(std::vector<EntityData*> pEntities);
    private:
        virtual void RenderEntity(const EntityData* pEntity) = 0;
    };
}

#endif 