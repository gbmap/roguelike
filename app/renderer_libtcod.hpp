#ifndef RENDERER_LIBTCOD_H
#define RENDERER_LIBTCOD_H

#include "renderer.hpp"

#include <libtcod.hpp>
#include <string>

namespace roguelike
{
    TCOD_ColorRGB ColorToTCODColor(const color_t& color)
    {
        return TCOD_ColorRGB{color.r, color.g, color.b};
    }

    class RendererTCOD : public Renderer
    {
    public:
        RendererTCOD(TCOD_Console& console) : m_console(console) {}

        void RenderEntity(const EntityData* pEntity) override
        {
            tcod::print(
                m_console, 
                {pEntity->position.GetX(), pEntity->position.GetY()}, 
                std::string(1, pEntity->symbol),
                ColorToTCODColor(pEntity->foreground_color),
                ColorToTCODColor(pEntity->background_color)
            );
        }

    private:
        TCOD_Console& m_console;
    };


}

#endif