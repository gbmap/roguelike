

#ifndef RENDERER_H
#define RENDERER_H

#include "../data.hpp"
#include "../math/vec2d.hpp"
#include "entity.hpp"
#include <vector>

namespace roguelike
{
    class IRenderable
    {
    public:
        void Draw(const Renderer* renderer) const;
    };

    class AnimatedRenderable : public IRenderable
    {
    public:

    };

    /*
        Responsible for rendering every IRenderable to the screen.
        Using the observer pattern, listens to created and destroyed IRenderables
        and renders them on command.
    */
    class Renderer
    {
    public:
        virtual void Clear() = 0;
        void Render(const std::vector<Entity*> pEntities) const;
        virtual void Render(const WorldRepresentation& r, const vec2di& p) const = 0;
        virtual void Present() = 0;
    private:
    };
}

#endif 