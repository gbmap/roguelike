

#ifndef RENDERER_H
#define RENDERER_H

#include "../data.hpp"
#include "../math/vec2d.hpp"
#include "entity.hpp"
#include <vector>

namespace roguelike
{
    class Renderer
    {
    public:
        virtual void Clear() = 0;
        void Render(const std::vector<Entity*> pEntities) const;
        virtual void Present() = 0;
    private:
        virtual void Render(const WorldRepresentation& r, const vec2di& p) const = 0;
    };
}

#endif 