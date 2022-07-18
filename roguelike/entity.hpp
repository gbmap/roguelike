
#pragma once 

#include "../data.hpp"
#include "../math/vec2d.hpp"
#include "commands/entity_command.hpp"
#include <vector>

namespace roguelike {
    class World;
    class Renderer;
    class Entity {
    public:
        Entity(const WorldRepresentation& r, const vec2di& p) : world_representation(r), position(p) {}
        const WorldRepresentation& GetRepresentation() const;

        void SetPosition(int x, int y);
        const vec2di& GetPosition() const;

        commands::EntityCommand* GetNextAction(const World& world);
        

        void Draw(const Renderer* renderer) const;
    private:
        vec2di position;
        WorldRepresentation world_representation;
        Stats stats;
    };

    typedef std::vector<Entity*> EntityVector;
}