
#pragma once 

#include "../data.hpp"
#include "../math/vec2d.hpp"
#include "commands/command.hpp"

namespace roguelike {
    class World;
    class Entity {
    public:
        Entity(const WorldRepresentation& r, const vec2di& p) : world_representation(r), position(p) {}
        const WorldRepresentation& GetRepresentation() const;
        const vec2di& GetPosition() const;

        commands::Command* GetNextAction(World& world);
    private:
        vec2di position;
        WorldRepresentation world_representation;
        Stats stats;
    };
}